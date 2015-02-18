#!/bin/bash 

RUN=`grep -o "RunSummary?RUN=......" RunSummary.html -m1  |  sed -r 's/^.{15}//'`

echo Starting on run... $RUN

COUNTER=1
until [  $COUNTER -gt 2 ]; do
    echo COUNTER $COUNTER

    # Which is the run?
    RUN=`grep -o "RunSummary?RUN=......" RunSummary.html -m1  |  sed -r 's/^.{15}//'`

    # Run CMSSW Programs
    cmsRun CTP7ToDigiAndDQM_cfg.py >& capture.log

    # Check Run has not changed
    RUN2=`grep -o "RunSummary?RUN=......" RunSummary.html -m1  |  sed -r 's/^.{15}//'`

    if [ $RUN != $RUN2 ]; then
		echo New Run is $RUN2
		let RUN=$RUN2
		echo Binning this data, change of run 
		echo I am going to sleep 5m  
		sleep 3m
    else 
		echo Now plotting! $RUN 
		
		#hadd -f CTP7DQMMERGE.root run.root CTP7DQM.root
		cp CTP7DQM.root CTP7DQMMERGE.root # i got an error again, why?
		# Plot
		root -b -q fastplotter.C >& plots.txt 
		root -b -q pumplotter.C >& pumplots.txt  
		root -b -q linkplotter.C >& linkplots.txt  
		#mv CTP7DQMMERGE.root run.root

                # Format for web
                foldername="CosmicsMonitoring_"$RUN"_"$COUNTER$(date +_%Y%m%d_%H%M%S)
                echo Creating $foldername

                mkdir -p "$foldername" 
                mv *png  "$foldername"
                cp templates/*Details.html "$foldername"
                mv *txt *log "$foldername"
                mv CTP7ToDigi.root "$foldername" 
		(cat templates/index_a ; echo RUN NUMBER: $RUN ;  cat templates/index_b) > index.html
		mv index.html "$foldername"
             	
                mv CTP7DQM.root  "$foldername"
                rm *.root
                
                cp  "$foldername"/*png "$foldername"/index.html /afs/cern.ch/user/r/rctcmstr/www/

	        mv "$foldername" ../archive

   fi 
   let COUNTER+=1
done
    
