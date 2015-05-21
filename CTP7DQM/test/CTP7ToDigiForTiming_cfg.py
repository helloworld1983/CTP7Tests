import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')

options.parseArguments()

process = cms.Process("myDQM")
process.load("DQMServices.Core.DQM_cfg")
process.load("DQMServices.Components.DQMEnvironment_cfi")
process.load("CTP7Tests.CTP7DQM.linkFilter_cfi")

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

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(3500) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(102) )

process.source = cms.Source("EmptySource")


process.ctp7ToDigi = cms.EDProducer('CTP7ToDigi',
                                    ctp7Host = cms.untracked.string("127.0.0.1"),  #LOCALHOST
                                    #ctp7Host = cms.untracked.string("144.92.181.245"),
                                    ctp7Port = cms.untracked.string("5554"),  # 5554 for raven3
                                    test = cms.untracked.bool(False),
                                    NEventsPerCapture = cms.untracked.int32(169),
                                    createLinkFile = cms.untracked.bool(True),
                                    doTimingScan = cms.untracked.bool(True))

filter_step = process.filterLinks

process.dqmSaver.workflow = cms.untracked.string('/L1TMonitor/Calo/CTP7')

process.l1tctp7 = cms.EDAnalyzer("L1TCTP7",
    DQMStore = cms.untracked.bool(True),
    disableROOToutput = cms.untracked.bool(False),
    outputFile = cms.untracked.string('./CTP7DQM.root'),
    ctp7Source = cms.InputTag("ctp7ToDigi"),
    verbose = cms.untracked.bool(False),
    filterTriggerType  = cms.int32(-1)
)

process.ctp7link = cms.EDAnalyzer("LinkDQM",
    DQMStore = cms.untracked.bool(True),
    disableROOToutput = cms.untracked.bool(False),
    outputFile = cms.untracked.string('./CTP7DQM.root'),
    ctp7Source = cms.InputTag("ctp7ToDigi"),
    verbose = cms.untracked.bool(False)
)


#This creates DQM-compatible plots
process.p = cms.Path(process.ctp7ToDigi+process.ctp7link+filter_step+process.l1tctp7+process.dqmSaver)


process.o1 = cms.OutputModule("PoolOutputModule",
                              outputCommands = cms.untracked.vstring('keep *'),
                              fileName = cms.untracked.string('CTP7ToDigi.root'))
process.outpath = cms.EndPath(process.o1)
