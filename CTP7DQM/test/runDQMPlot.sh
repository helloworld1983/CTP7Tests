#!/bin/bash
cmsRun CTP7DQM_cfg.py   >& dqm.log 
root -b -q fastplotter.C >& plots.log 
root -b -q pumplotter.C >& pumplots.log 

foldername=$(date +%Y%m%d_%H%M%S)
mkdir -p "$foldername" 
cp *png *log  "$foldername"
cp CTP7DQM.root  "$foldername"
rm DQM_V0001_R000000001__L1TMonitor__Calo__CTP7.root
cp index.html "$foldername"

mkdir -p ~/www/CTP7DQMTESTS/
mv "$foldername"  ~/www/CTP7DQMTESTS/

