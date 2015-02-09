#ifndef L1TCTP7_H
#define L1TCTP7_H

// system include files
#include <memory>
#include <unistd.h>


#include <iostream>
#include <fstream>
#include <vector>


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

// DQM
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"


// GCT and RCT data formats
#include "DataFormats/L1CaloTrigger/interface/L1CaloCollections.h"

//
// class declaration
//

class L1TCTP7 : public edm::EDAnalyzer {

public:

// Constructor
  L1TCTP7(const edm::ParameterSet& ps);

// Destructor
 virtual ~L1TCTP7();

protected:
// Analyze
 void analyze(const edm::Event& e, const edm::EventSetup& c);

// BeginRun
  void beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup);

// BeginJob
 void beginJob(void);

// EndJob
void endJob(void);

private:
  // ----------member data ---------------------------
  DQMStore * dbe;

  // trigger type information
  MonitorElement *triggerType_;

  // region global coordinates
  MonitorElement* ctp7RegionsEtEtaPhi_;
  MonitorElement* ctp7RegionsOccEtaPhi_;

  // region local coordinates
  MonitorElement* ctp7RegionsLocalEtEtaPhi_;
  MonitorElement* ctp7RegionsLocalOccEtaPhi_;
  MonitorElement* ctp7TauVetoLocalEtaPhi_;

  // Region rank
  MonitorElement* ctp7RegionRank_;
  //PUM plot
  MonitorElement* ctp7RegionsNonZero_;
  MonitorElement* ctp7RegionsNonZeroVsEvt_;
  MonitorElement* ctp7RegionsAvgEtVsEvt_;
  MonitorElement* ctp7RegionsMaxEtVsEvt_;
  MonitorElement* ctp7RegionsAverageRegionEt_;
  MonitorElement* ctp7RegionsAvgEtVsEta_;
  MonitorElement* ctp7RegionsPumEta0_;
  MonitorElement* ctp7RegionsPumEta1_;
  MonitorElement* ctp7RegionsPumEta2_;
  MonitorElement* ctp7RegionsPumEta3_;
  MonitorElement* ctp7RegionsPumEta4_;
  MonitorElement* ctp7RegionsPumEta5_;
  MonitorElement* ctp7RegionsPumEta6_;
  MonitorElement* ctp7RegionsPumEta7_;
  MonitorElement* ctp7RegionsPumEta8_;
  MonitorElement* ctp7RegionsPumEta9_;
  MonitorElement* ctp7RegionsPumEta10_;
  MonitorElement* ctp7RegionsPumEta11_;
  MonitorElement* ctp7RegionsPumEta12_;
  MonitorElement* ctp7RegionsPumEta13_;
  MonitorElement* ctp7RegionsPumEta14_;
  MonitorElement* ctp7RegionsPumEta15_;
  MonitorElement* ctp7RegionsPumEta16_;
  MonitorElement* ctp7RegionsPumEta17_;
  MonitorElement* ctp7RegionsPumEta18_;
  MonitorElement* ctp7RegionsPumEta19_;
  MonitorElement* ctp7RegionsPumEta20_;
  MonitorElement* ctp7RegionsPumEta21_;


  MonitorElement* ctp7OverFlowEtaPhi_;
  MonitorElement* ctp7TauVetoEtaPhi_;
  MonitorElement* ctp7MipEtaPhi_;
  MonitorElement* ctp7QuietEtaPhi_;
  MonitorElement* ctp7HfPlusTauEtaPhi_;

  // Bx
  MonitorElement *ctp7RegionBx_;
  MonitorElement *ctp7EmBx_;

  // em
  // HW coordinates
  MonitorElement *ctp7EmCardRegion_;


  MonitorElement* ctp7IsoEmEtEtaPhi_;
  MonitorElement* ctp7IsoEmOccEtaPhi_;
  MonitorElement* ctp7NonIsoEmEtEtaPhi_;
  MonitorElement* ctp7NonIsoEmOccEtaPhi_;
  MonitorElement* ctp7IsoEmRank_;
  MonitorElement* ctp7NonIsoEmRank_;


  int nev_; // Number of events processed
  std::string outputFile_; //file name for ROOT ouput
  bool verbose_;
  bool monitorDaemon_;
  std::ofstream logFile_;
  
  edm::EDGetTokenT<L1CaloRegionCollection> ctp7Source_L1CRCollection_;
  edm::EDGetTokenT<L1CaloEmCollection> ctp7Source_L1CEMCollection_;
  
  /// filter TriggerType
  int filterTriggerType_;

};

#endif
