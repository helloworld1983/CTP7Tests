#!/bin/bash

while [ "$1" != "" ]; do
    case $1 in
        -h | --help )               echo "runContinuous.sh usage: bash runContinuous.sh [-h] [n_iterations]"
                                    exit 1
                                    ;;
        * )                         N_ITERATIONS=$1
                                    ;;
    esac
    shift
done

if [ "$N_ITERATIONS" == "" ]; then
    N_ITERATIONS=1
fi

echo "Checking TimingTests "$N_ITERATIONS" time"$MAYBE_AN_S"..."


COUNTER=1
until [  $COUNTER -gt "$N_ITERATIONS" ]; do
	echo COUNTER $COUNTER

	cmsRun RCTToDigi_cfg.py   >& rct.log 
	cmsRun L1ADQM_cfg.py   >& dqm.log

	#if [ -f mergeOLD.root ]
	#	then
	#			hadd  merge.root mergeOLD.root L1ADQM.root
	#			mv L1ADQM.root L1ADQM_$COUNTER.root

	#			mv merge.root L1ADQM.root  

	#	else 

	#		cp L1ADQM.root L1ADQM_$COUNTER.root             
	#	fi 

	hadd merge.root mergeOLD.root L1ADQM.root
	mv L1ADQM.root L1ADQM_$COUNTER.root
	mv merge.root L1ADQM.root  
	root -b -q macros/fastplotter.C >& plots.log 
	root -b -q macros/linkplotter.C >& plots.log 
	mv L1ADQM.root mergeOLD.root 

	foldername=$(date +%Y%m%d_%H%M%S)
	mkdir -p "$foldername" 
	cp *png *log  "$foldername"
	cp mergeOLD.root L1ADQM_$COUNTER.root RCTToDigi.root  "$foldername"
	rm DQM_V0001_R000000001__L1TMonitor__Calo__CTP7.root
	cp index.html "$foldername"
	cp rct.log /afs/cern.ch/user/r/rctcmstr/www/L1A/.
	cp *png /afs/cern.ch/user/r/rctcmstr/www/L1A/. 

	let COUNTER+=1

	done



