import FWCore.ParameterSet.Config as cms

process = cms.Process("myDQM")
process.load("DQMServices.Core.DQM_cfg")
process.load("DQMServices.Components.DQMEnvironment_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(64)
)

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
"file:/afs/cern.ch/user/g/ginnocen/public/L1T_PACK_stage1_EDM.root"
)
)

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.MessageLogger = cms.Service("MessageLogger",
    destinations = cms.untracked.vstring('detailedInfo'),
    detailedInfo = cms.untracked.PSet(
            default = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
            threshold = cms.untracked.string('DEBUG')
    )
)

process.dqmSaver.workflow = cms.untracked.string('/L1TMonitor/Calo/CTP7')

process.l1tctp7 = cms.EDAnalyzer("L1TCTP7",
    DQMStore = cms.untracked.bool(True),
    disableROOToutput = cms.untracked.bool(False),
    outputFile = cms.untracked.string('./CTP7DQMMC.root'),
    ctp7Source = cms.InputTag("simRctDigis"),
#    ctp7Source = cms.InputTag("caloStage1Digis"),
    verbose = cms.untracked.bool(False),
    filterTriggerType  = cms.int32(-1)
)

#This creates DQM-compatible plots
process.p = cms.Path(process.l1tctp7+process.dqmSaver)



