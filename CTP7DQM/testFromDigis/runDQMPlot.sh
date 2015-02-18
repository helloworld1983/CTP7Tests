#!/bin/bash 
# Run CMSSW Programs
cmsRun CTP7DQM_cfg.py   >& dqm.log 

# Plot
root -b -q macros/fastplotterMC.C >& plots.log 

# Format for web
foldername="TestFromDigis"_$(date +_%Y%m%d_%H%M%S)
echo Creating $foldername

mkdir -p "$foldername" 
mv *png  "$foldername"
mv *log "$foldername"
cp templates/indexMC.html "$foldername"/index.html
cp templates/*Details.html "$foldername"

mv CTP7DQMMC.root  "$foldername"
rm DQM_*__L1TMonitor__Calo__CTP7.root

#    If you have access to a www folder you can do this     
#    mkdir -p ~/www/CTP7DQMTESTS/testforIsobel
#    cp  "$foldername"/* ~/www/CTP7DQMTESTS/testforIsobel/
    

    
