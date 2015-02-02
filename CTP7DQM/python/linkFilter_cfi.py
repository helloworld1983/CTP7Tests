#flake8: noqa
import FWCore.ParameterSet.Config as cms

'''
Select only events with good links
Authors: Laura Dodd, Maria Cepeda
'''

linkEDFilter = cms.EDFilter(
    "LinkFilter",
    ctp7Source = cms.InputTag("ctp7ToDigi"),
)

filterLinks = cms.Sequence(
    linkEDFilter
)

