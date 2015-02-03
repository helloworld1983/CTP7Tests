#include "CTP7Tests/LinkMonitor/interface/LinkMonitor.h"
#include "CTP7Tests/TimeMonitor/interface/TimeMonitor.h"
#include "CTP7Tests/CTP7DQM/interface/LinkDQM.h"
#include "DataFormats/Provenance/interface/EventAuxiliary.h"

//DQMStore
#include "DQMServices/Core/interface/DQMStore.h"




using namespace edm;

ofstream myfile;

// Ranks 6, 10 and 12 bits
const unsigned int R6BINS = 64;
const float R6MIN = -0.5;
const float R6MAX = 63.5;
const unsigned int R10BINS = 1024;
const float R10MIN = -0.5;
const float R10MAX = 1023.5;

const unsigned int NILINKS = 36;
const float NILINKSMIN = -0.5;
const float NILINKSMAX = 35.5;

const unsigned int NUINT = 7e4;

const unsigned int TIMEBINS = 245959;
const float TIMEMIN = -0.5;
const float TIMEMAX = 245958.5;



LinkDQM::LinkDQM(const ParameterSet & ps) :
	ctp7Source_LMCollection_( consumes<LinkMonitorCollection>(ps.getParameter< InputTag >("ctp7Source") )),
	ctp7Source_TCollection_( consumes<TimeMonitorCollection>(ps.getParameter< InputTag >("ctp7Source") ))
{





	// verbosity switch
	verbose_ = ps.getUntrackedParameter < bool > ("verbose", true);

	if (verbose_)
		std::cout << "LinkDQM: constructor...." << std::endl;


	dbe = NULL;
	if (ps.getUntrackedParameter < bool > ("DQMStore", false)) {
		dbe = Service < DQMStore > ().operator->();
		//		dbe->setVerbose(0);
	}

	outputFile_ =
		ps.getUntrackedParameter < std::string > ("outputFile", "");
	if (outputFile_.size() != 0) {
		std::
			cout << "L1T Monitoring histograms will be saved to " <<
			outputFile_.c_str() << std::endl;
	}

	bool disable =
		ps.getUntrackedParameter < bool > ("disableROOToutput", false);
	if (disable) {
		outputFile_ = "";
	}


	if (dbe != NULL) {
		dbe->setCurrentFolder("L1T/LinkDQM");
	}


}

LinkDQM::~LinkDQM()
{
}

void LinkDQM::beginJob(void)
{

	nev_ = 0;
        myfile.open ("links.log");
}

void LinkDQM::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
	//Only histograms booking

	// get hold of back-end interface
	DQMStore *dbe = 0;
	dbe = Service < DQMStore > ().operator->();

	std::cout << "LinkDQM: begin run...." << std::endl;
	if (dbe) {
		dbe->setCurrentFolder("L1T/LinkDQM");

		// global regions
		ctp7LinkMonitor_ = 
			dbe->book1D("RctLinkMonitor", "LINK MONITOR",NUINT, 0.,NUINT );
		ctp7LinkMonitorNot15_ = 
			dbe->book1D("RctLinkMonitorNot15", "LINK MONITOR NOT 0xf",NUINT,0., NUINT);
		ctp7LinkMonitor2D_ = 
			dbe->book2D("RctLinkMonitor2D", "LINK MONITOR 2D", NILINKS, NILINKSMIN, NILINKSMAX,2,-0.5,1.5);
		ctp7LinkMonitorNot15_2D_ = 
			dbe->book2D("RctLinkMonitorNot15_2D", "LINK MONITOR 2D Not 0xf", NILINKS, NILINKSMIN, NILINKSMAX,NUINT,0.,NUINT);
		ctp7LinkMonitorVsTime_ = 
			dbe->book2D("RctLinkMonitorVsTime", "LINK MONITOR Vs Time", TIMEBINS,TIMEMIN,TIMEMAX,NILINKS, NILINKSMIN, NILINKSMAX);
	}
}

void LinkDQM::endJob(void)
{
	if (verbose_)
	LogInfo("EndJob") << "analyzed " << nev_ << " events";

	if (outputFile_.size() != 0 && dbe)
		dbe->save(outputFile_);

        myfile.close();

	return;
}

void LinkDQM::analyze(const Event & e, const EventSetup & c)
{
	nev_++;
	if (verbose_) {
		std::cout << "LinkDQM: analyze...." << std::endl;
	}

	// Get the RCT digis
	edm::Handle < LinkMonitorCollection > lm;
	edm::Handle < TimeMonitorCollection > time;

	bool doLm = true;

	e.getByToken(ctp7Source_LMCollection_,lm);
	e.getByToken(ctp7Source_TCollection_,time);

	if (!lm.isValid()) {
		edm::LogInfo("DataNotFound") << "can't find LinkMonitor";
		doLm = false;
	}

        unsigned int date;
        unsigned int clock;
        for (TimeMonitorCollection::const_iterator t = time->begin(); t != time->end(); t++){
                date=t->date();
                clock=t->minute();
	}

	if ( doLm ) {
                int i =0;
                int numbadlinks =0;
		for (LinkMonitorCollection::const_iterator link = lm->begin(); link != lm->end(); link++) {
			ctp7LinkMonitor_->Fill(link->raw());
		        if (link->raw()!=15) {
			        ctp7LinkMonitor2D_->Fill(i,1);
			        ctp7LinkMonitorNot15_->Fill(link->raw());
			        ctp7LinkMonitorNot15_2D_->Fill(i,link->raw());
				ctp7LinkMonitorVsTime_->Fill(clock,i);
				myfile <<"Time: date: "<<date <<"; clock time: "<<clock <<std::endl;
				myfile <<"Link "<<i<<" is not 15!"<<std::endl;
				myfile <<"Link "<<i<<" is: "<< link->raw()<<std::endl;
				numbadlinks++;
                         }	
			else{
			        ctp7LinkMonitor2D_->Fill(i,0);
			}
			i++;
		}
	}

}
