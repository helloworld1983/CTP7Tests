#!/bin/bash
cmsRun RCTToDigi_cfg.py   >& rct.log 
cmsRun L1ADQM_cfg.py   >& dqm.log 
mv L1ADQM.root L1ADQMMERGED.root
root -b -q macros/fastplotter.C >& plots.log 
root -b -q macros/linkplotter.C >& plots.log 


foldername=$(date +%Y%m%d_%H%M%S)
mkdir -p "$foldername" 
rm DQM_V0001_R000000001__L1TMonitor__Calo__CTP7.root
cp index.html "$foldername"
cp index.html /afs/cern.ch/user/r/rctcmstr/www/L1A/.
mv rct.log /afs/cern.ch/user/r/rctcmstr/www/L1A/.
cp *png /afs/cern.ch/user/r/rctcmstr/www/L1A/. 
mv *png *log  "$foldername"
mv L1ADQM*.root RCTToDigi.root "$foldername"

