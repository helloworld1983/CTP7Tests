/*
 * \file RCTL1A.cc
 *
 * \author P. Wittich
 *
 */

#include "CTP7Tests/CTP7DQM/interface/RCTL1A.h"
#include "DataFormats/Provenance/interface/EventAuxiliary.h"

//DQMStore
#include "DQMServices/Core/interface/DQMStore.h"




using namespace edm;

const unsigned int NUMREGIONS = 396;

const unsigned int PHIBINS = 18;
const float PHIMIN = -0.5;
const float PHIMAX = 17.5;

// Ranks 6, 10 and 12 bits
const unsigned int R6BINS = 64;
const float R6MIN = -0.5;
const float R6MAX = 63.5;
const unsigned int R10BINS = 1024;
const float R10MIN = -0.5;
const float R10MAX = 1023.5;

const unsigned int ETABINS = 22;
const float ETAMIN = -0.5;
const float ETAMAX = 21.5;

const unsigned int EVBINS = 400;
const float EVMIN = -0.5;
const float EVMAX = 399.5;



const unsigned int PUMBINS = 22;
const float PUMMIN = -0.5;
const float PUMMAX = 21.5;

RCTL1A::RCTL1A(const ParameterSet & ps) :
	ctp7Source_L1CRCollection_( consumes<L1CaloRegionCollection>(ps.getParameter< InputTag >("ctp7Source") )),
	ctp7Source_L1CEMCollection_( consumes<L1CaloEmCollection>(ps.getParameter< InputTag >("ctp7Source") )),
	filterTriggerType_ (ps.getParameter< int >("filterTriggerType"))
{

	// verbosity switch
	verbose_ = ps.getUntrackedParameter < bool > ("verbose", false);

	if (verbose_)
		std::cout << "RCTL1A: constructor...." << std::endl;


	dbe = NULL;
	if (ps.getUntrackedParameter < bool > ("DQMStore", false)) {
		dbe = Service < DQMStore > ().operator->();
		dbe->setVerbose(0);
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
		dbe->setCurrentFolder("L1T/RCTL1A");
	}


}

RCTL1A::~RCTL1A()
{
}

void RCTL1A::beginJob(void)
{
	nev_ = 0;
}

void RCTL1A::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
	//Only histograms booking

	// get hold of back-end interface
	DQMStore *dbe = 0;
	dbe = Service < DQMStore > ().operator->();

	if (dbe) {
		dbe->setCurrentFolder("L1T/RCTL1A");

		triggerType_ =
			dbe->book1D("TriggerType", "TriggerType", 17, -0.5, 16.5);
		// global regions
		ctp7RegionsAvgEtVsEta_ =
			dbe->book2D("RctRegionsAvgEtVsEta", " AVERAGE REGION RANK vs ETA", ETABINS, ETAMIN, ETAMAX, R10BINS, R10MIN, R10MAX);

		// global regions
		ctp7RegionsEtEtaPhi_ =
			dbe->book2D("RctRegionsEtEtaPhi", "REGION E_{T}", ETABINS, ETAMIN,
					ETAMAX, PHIBINS, PHIMIN, PHIMAX);
		ctp7RegionsOccEtaPhi_ =
			dbe->book2D("RctRegionsOccEtaPhi", "REGION OCCUPANCY", ETABINS,
					ETAMIN, ETAMAX, PHIBINS, PHIMIN, PHIMAX);
		ctp7IsoEmEtEtaPhi_ =
			dbe->book2D("RctEmIsoEmEtEtaPhi", "ISO EM E_{T}", ETABINS, ETAMIN,
					ETAMAX, PHIBINS, PHIMIN, PHIMAX);
		ctp7IsoEmOccEtaPhi_ =
			dbe->book2D("RctEmIsoEmOccEtaPhi", "ISO EM OCCUPANCY", ETABINS,
					ETAMIN, ETAMAX, PHIBINS, PHIMIN, PHIMAX);
		ctp7NonIsoEmEtEtaPhi_ =
			dbe->book2D("RctEmNonIsoEmEtEtaPhi", "NON-ISO EM E_{T}", ETABINS,
					ETAMIN, ETAMAX, PHIBINS, PHIMIN, PHIMAX);
		ctp7NonIsoEmOccEtaPhi_ =
			dbe->book2D("RctEmNonIsoEmOccEtaPhi", "NON-ISO EM OCCUPANCY",
					ETABINS, ETAMIN, ETAMAX, PHIBINS, PHIMIN, PHIMAX);

		// Region rank histos
		ctp7RegionRank_ =
			dbe->book1D("RctRegionRank", "REGION RANK", R10BINS, R10MIN,
					R10MAX);
		//EM Rank
		ctp7IsoEmRank_ =
			dbe->book1D("RctEmIsoEmRank", "ISO EM RANK", R6BINS, R6MIN, R6MAX);
		ctp7NonIsoEmRank_ =
			dbe->book1D("RctEmNonIsoEmRank", "NON-ISO EM RANK", R6BINS, R6MIN,
					R6MAX);
		// bx histos
//		ctp7RegionBx_ = dbe->book1D("RctRegionBx", "Region BX", 5, 0, 5);
//		ctp7EmBx_ = dbe->book1D("RctEmBx", "EM BX", 5, 0, 5);
                ctp7RegionBx_ = dbe->book1D("RctRegionBx", "Region BX", 5, -2.5, 2.5);
                ctp7EmBx_ = dbe->book1D("RctEmBx", "EM BX", 5, -2.5, 2.5);

	}
}

void RCTL1A::endJob(void)
{
	if (verbose_)
		std::cout << "RCTL1A: end job...." << std::endl;
	LogInfo("EndJob") << "analyzed " << nev_ << " events";

	if (outputFile_.size() != 0 && dbe)
		dbe->save(outputFile_);

	return;
}

void RCTL1A::analyze(const Event & e, const EventSetup & c)
{
	nev_++;
	if (verbose_) {
		std::cout << "RCTL1A: analyze...." << std::endl;
	}

	// fill a histogram with the trigger type, for normalization fill also last bin
	// ErrorTrigger + 1
	double triggerType = static_cast<double> (e.experimentType()) + 0.001;
	double triggerTypeLast = static_cast<double> (edm::EventAuxiliary::ExperimentType::ErrorTrigger)
		+ 0.001;
	triggerType_->Fill(triggerType);
	triggerType_->Fill(triggerTypeLast + 1);

	// filter only if trigger type is greater than 0, negative values disable filtering
	if (filterTriggerType_ >= 0) {

		// now filter, for real data only
		if (e.isRealData()) {
			if (!(e.experimentType() == filterTriggerType_)) {

				edm::LogInfo("RCTL1A") << "\n Event of TriggerType "
					<< e.experimentType() << " rejected" << std::endl;
				return;

			}
		}

	}

	// Get the RCT digis
	edm::Handle < L1CaloEmCollection > em;
	edm::Handle < L1CaloRegionCollection > rgn;

	bool doEm = true;
	bool doHd = true;

	e.getByToken(ctp7Source_L1CRCollection_,rgn);

	if (!rgn.isValid()) {
		edm::LogInfo("DataNotFound") << "can't find L1CaloRegionCollection";
		doHd = false;
	}

	if ( doHd ) {
		// Fill the RCT histograms
		int nonzeroregions = 0;
		int totalregionet = 0;
		int maxregionet = 0;

		// Regions
		for (L1CaloRegionCollection::const_iterator ireg = rgn->begin();
				ireg != rgn->end(); ireg++) {
			ctp7RegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
			if(ireg->et()>0)
			{
				nonzeroregions++;
				totalregionet += ireg->et();
				if(ireg->et()>maxregionet) maxregionet=ireg->et();        

				ctp7RegionRank_->Fill(ireg->et());
				if(ireg->et()>5){
					ctp7RegionsOccEtaPhi_->Fill(ireg->gctEta(), ireg->gctPhi());
				}
				ctp7RegionsEtEtaPhi_->Fill(ireg->gctEta(), ireg->gctPhi(), ireg->et());

				ctp7RegionBx_->Fill(ireg->bx()-2);  // -2 to have it centered in 0
			}
		}//end region loop
	}//end doHd


	e.getByToken(ctp7Source_L1CEMCollection_,em);

	if (!em.isValid()) {
		edm::LogInfo("DataNotFound") << "can't find L1CaloEmCollection";
		doEm = false;
	}
	if ( ! doEm ) return;
	// Isolated and non-isolated EM
	for (L1CaloEmCollection::const_iterator iem = em->begin();
			iem != em->end(); iem++) {
		if (iem->rank()>0){
			ctp7EmBx_->Fill(iem->bx()-2); // -2 to have it centered in 0
			if (iem->isolated()){
				ctp7IsoEmRank_->Fill(iem->rank());
				ctp7IsoEmEtEtaPhi_->Fill(iem->regionId().ieta(),
						iem->regionId().iphi(), iem->rank());

				if (iem->rank()>10){
					ctp7IsoEmOccEtaPhi_->Fill(iem->regionId().ieta(),
							iem->regionId().iphi());
				}
			}
			else{
				ctp7NonIsoEmRank_->Fill(iem->rank());
				ctp7NonIsoEmEtEtaPhi_->Fill(iem->regionId().ieta(),
						iem->regionId().iphi(), iem->rank());
				if (iem->rank()>10){
					ctp7NonIsoEmOccEtaPhi_->Fill(iem->regionId().ieta(),
							iem->regionId().iphi());
				}
			} 
		}
	}

}
