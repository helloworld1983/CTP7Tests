import FWCore.ParameterSet.Config as cms

process = cms.Process("myDQM")
process.load("DQMServices.Core.DQM_cfg")
process.load("DQMServices.Components.DQMEnvironment_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    'file:RCTToDigi.root'
)
)

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.MessageLogger = cms.Service("MessageLogger",
    destinations = cms.untracked.vstring('detailedInfo'),
    detailedInfo = cms.untracked.PSet(
            default = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
            threshold = cms.untracked.string('DEBUG')
           #threshold = cms.untracked.string('ERROR')
    )
)

#process.load("CTP7Tests.CTP7DQM.linkFilter_cfi")

#filter_step = process.filterLinks

process.dqmSaver.workflow = cms.untracked.string('/L1TMonitor/Calo/CTP7')

process.l1tctp7 = cms.EDAnalyzer("RCTL1A",
    DQMStore = cms.untracked.bool(True),
    disableROOToutput = cms.untracked.bool(False),
    outputFile = cms.untracked.string('./L1ADQM.root'),
    ctp7Source = cms.InputTag("rctToDigi"),
    verbose = cms.untracked.bool(True),
    filterTriggerType  = cms.int32(-1)
)


process.ctp7link = cms.EDAnalyzer("LinkDQM",
    DQMStore = cms.untracked.bool(True),
    disableROOToutput = cms.untracked.bool(False),
    outputFile = cms.untracked.string('./L1ADQM.root'),
    ctp7Source = cms.InputTag("rctToDigi"),
    verbose = cms.untracked.bool(False)
)


#This creates DQM-compatible plots
process.p = cms.Path(process.l1tctp7+process.ctp7link+process.dqmSaver)

# For faster debugging & extra couts we can also work with a standard analyzer
#process.ctp7protodqm = cms.EDAnalyzer('CTP7DQM')
#process.TFileService = cms.Service(
#  "TFileService",
#  fileName = cms.string("test.root")
#  )
#process.p2 = cms.Path(process.ctp7protodqm)

