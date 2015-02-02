// -*- C++ -*-
//
// Package:    CTP7Tests/LinkFilter
// Class:      LinkFilter
// 
/**\class LinkFilter LinkFilter.cc CTP7Tests/LinkFilter/plugins/LinkFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Laura Dodd
//         Created:  Mon, 02 Feb 2015 12:52:36 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CTP7Tests/LinkMonitor/interface/LinkMonitor.h"
//
// class declaration
//

class LinkFilter : public edm::EDFilter {
   public:
      explicit LinkFilter(const edm::ParameterSet&);
      ~LinkFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      edm::EDGetTokenT<LinkMonitorCollection> ctp7Source_LMCollection_;
      
      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
LinkFilter::LinkFilter(const edm::ParameterSet& iConfig):
        ctp7Source_LMCollection_( consumes<LinkMonitorCollection>(iConfig.getParameter< edm::InputTag >("ctp7Source") ))
{
   //now do what ever initialization is needed

}


LinkFilter::~LinkFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
LinkFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   Handle < LinkMonitorCollection > lm;
   iEvent.getByToken(ctp7Source_LMCollection_,lm);

   bool goodLinks = true;
   for (LinkMonitorCollection::const_iterator link = lm->begin(); link != lm->end(); link++) {
         if (link->raw()!=15) {goodLinks=false;}
   }
   if (!goodLinks) return false;
   else{ return true;}
}

// ------------ method called once each job just before starting event loop  ------------
void 
LinkFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
LinkFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
LinkFilter::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
LinkFilter::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
LinkFilter::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
LinkFilter::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
LinkFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(LinkFilter);
