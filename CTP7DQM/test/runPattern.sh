#!/bin/bash 

while [ "$1" != "" ]; do
    case $1 in
	-h | --help )               echo "runPattern.sh usage: ./runPattern.sh [-h] [n_iterations] [--wait n_minutes]"
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

echo "Checking Patterns "$N_ITERATIONS" time"$MAYBE_AN_S"..."

COUNTER=1
until [  $COUNTER -gt "$N_ITERATIONS" ]; do
   echo COUNTER $COUNTER

   # Run CMSSW Programs
   cmsRun CTP7ToDigi_cfg.py >& capture.log
   cmsRun CTP7DQM_cfg.py >& dqm.log

   cp CTP7DQM.root CTP7DQMMERGE.root 
   # Plot
   root -b -q fastplotter.C >& plots.txt 
   root -b -q pumplotter.C >& pumplots.txt  
   root -b -q linkplotter.C >& linkplots.txt  

   # Format for web
   foldername="TestsRCTToMP7_"$COUNTER$(date +_%Y%m%d_%H%M%S)
   echo Creating $foldername

   mkdir -p "$foldername" 
   mv *png  "$foldername"
   cp templates/*Details.html "$foldername"
   mv *txt *log "$foldername"
   mv CTP7ToDigi.root "$foldername" 
   (cat templates/index_a ; echo $foldername;  cat templates/index_b) > index.html
   mv index.html "$foldername"
     	
   mv CTP7DQM.root  "$foldername"
   rm *.root
        
   cp  "$foldername"/*png "$foldername"/index.html /afs/cern.ch/user/r/rctcmstr/www/

   mv "$foldername" ../archive/

   if [ "$COUNTER" != "$N_ITERATIONS" ]; then
       if [ "$WAIT_TIME" == "" ]; then
	   echo "Waiting 1 minute..."
	   sleep 1m
       else
	   echo "Waiting "$WAIT_TIME" minutes..."
	   sleep "$WAIT_TIME"m
       fi
   fi

   let COUNTER+=1
done
    
