#!/bin/bash 

while [ "$1" != "" ]; do
    case $1 in
	-h | --help )               echo "runTimingTest.sh usage: ./runTimingTest.sh [-h] [n_iterations] [--wait n_minutes]"
                                    exit 1
                                    ;;
	--wait )                    shift
                                    WAIT_TIME=$1
                                    ;;
	* )                         N_ITERATIONS=$1
                                    ;;
    esac
    shift
done

if [ "$N_ITERATIONS" == "" ]; then
    N_ITERATIONS=1
fi

if [ "$N_ITERATIONS" -gt 1 ]; then
    MAYBE_AN_S="s"
fi

echo "Checking TimingTests "$N_ITERATIONS" time"$MAYBE_AN_S"..."

COUNTER=1
until [  $COUNTER -gt "$N_ITERATIONS" ]; do
   echo COUNTER $COUNTER

   # Run CMSSW Programs
#   cmsRun CTP7ToDigi_cfg.py >& capture.log
#   cmsRun CTP7DQM_cfg.py >& dqm.log

   cmsRun CTP7ToDigiForTiming_cfg.py  >& capture.log

   cp CTP7DQM.root CTP7DQMMERGE.root 
   # Plot
   root -b -q fastplotter.C >& plots.txt 
   root -b -q pumplotter.C >& pumplots.txt  
   root -b -q timingplotter.C >& timeplots.txt  
   root -b -q linkplotter.C >& linkplots.txt  

   # Format for web
   foldername="2Bunches_COLLISIONS_TIMING_"$COUNTER$(date +_%Y%m%d_%H%M%S)
	   echo Creating $foldername

   mkdir -p "$foldername" 
   mv *png  "$foldername"
   mv *root  "$foldername"

   cp templates/*Details.html "$foldername"
   cp *txt *log "$foldername"
   #mv CTP7ToDigi.root "$foldername" 
   (cat templates/index_a ; echo $foldername;  cat templates/index_b) > index.html
   mv index.html "$foldername"
     	
   #mv CTP7DQM.root  "$foldername"
   #mv CTP7ToDigi.root  "$foldername"
   #rm *.root
        
   cp  "$foldername"/*  /afs/cern.ch/user/r/rctcmstr/www/TIMING
   cp -r "$foldername" /afs/cern.ch/user/r/rctcmstr/www/TIMING 

   mv "$foldername" ../archive/

   if [ "$COUNTER" != "$N_ITERATIONS" ]; then
       if [ "$WAIT_TIME" == "" ]; then
	   echo "Waiting 0 minute..."
	   sleep 0m
       else
	   echo "Waiting "$WAIT_TIME" minutes..."
	   sleep "$WAIT_TIME"m
       fi
   fi

   let COUNTER+=1

done
    
