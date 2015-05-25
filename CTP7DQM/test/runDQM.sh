#!/bin/bash 

while [ "$1" != "" ]; do
    case $1 in
        -h | --help )               echo "runDQM usage: "
                                    echo "    ./runDQM.sh [-h] [n_iterations] [--wait n_minutes] [--pattern] [--events n_events]"
                                    echo "        -h, --help   :   Print this message and exit"
                                    echo "        n_iterations :   Repeat test this many times"
                                    echo "        --wait       :   Minutes to wait between tests"
                                    echo "        --pattern    :   Pattern tests rather than continuous running"
                                    echo "        --events     :   Events to accumulate (default: 10000, 64 for pattern tests)"
                                    exit 1
                                    ;;
        --wait )                    shift
                                    WAIT_TIME=$1
                                    ;;
        --events )                  shift
                                    N_EVENTS=$1
                                    ;;
        --pattern )                 PATTERN=1
                                    ;;
        * )                         N_ITERATIONS=$1
                                    ;;
    esac
    shift
done

if [ "$N_ITERATIONS" == "" ]; then
    N_ITERATIONS=1
fi

if [ "$N_EVENTS" == "" ]; then
    if [ "$PATTERN" == 1 ]; then
        N_EVENTS=64
    else
        N_EVENTS=10000
    fi
fi
EVENT_STR="maxEvents="$N_EVENTS""

if [ "$N_ITERATIONS" -gt 1 ]; then
    MAYBE_AN_S="s"
fi

if [ "$PATTERN" != 1 ]; then
    RUN=`grep -o "RunSummary?RUN=......" templates/RunSummary.html -m1  |  sed -r 's/^.{15}//'`
    RUN_ADDENDUM="starting with run "$RUN""
fi

echo "Running DQM on "$N_EVENTS" events "$N_ITERATIONS" time"$MAYBE_AN_S" "$RUN_ADDENDUM" ..."

COUNTER=1
until [  $COUNTER -gt "$N_ITERATIONS" ]; do
    if [ "$COUNTER" -gt 1 -a "$WAIT_TIME" != "" ]; then
	echo "Next test in "$WAIT_TIME" minutes... good night"
	sleep "$WAIT_TIME"m
    fi

    echo TEST $COUNTER

    if [ "$PATTERN" != 1 ]; then
	# Which is the run?
	RUN=`grep -o "RunSummary?RUN=......" templates/RunSummary.html -m1  |  sed -r 's/^.{15}//'`
    fi

    # Run CMSSW Programs
    cmsRun CTP7ToDigiAndDQM_cfg.py "$EVENT_STR" >& capture.log #CTP7ToDigiAndDQM_cfg.py >& capture.log

    # if we're doing a pattern test or we did enough events within a run, plot stuff
    PLOT_NOW=1
    if [ "$PATTERN" != 1 ]; then
        # Check Run has not changed
	RUN2=`grep -o "RunSummary?RUN=......" templates/RunSummary.html -m1  |  sed -r 's/^.{15}//'`
	if [ $RUN != $RUN2 ]; then
            echo New Run is $RUN2
            PLOT_NOW=0
            echo Binning this data, change of run 
	fi
    fi
    
    # plot all the things
    if [ "$PLOT_NOW" == 1 ]; then
        echo Now plotting! $RUN 
        
        #hadd -f CTP7DQMMERGE.root run.root CTP7DQM.root
        cp CTP7DQM.root CTP7DQMMERGE.root # i got an error again, why?
        # Plot
        root -b -q fastplotter.C >& plots.txt 
        root -b -q pumplotter.C >& pumplots.txt  
        root -b -q linkplotter.C >& linkplots.txt  
        #mv CTP7DQMMERGE.root run.root
	
        # Format for web
	if [ "$PATTERN" != 1 ]; then
            foldername="CosmicsMonitoring_"$RUN"_"$COUNTER$(date +_%Y%m%d_%H%M%S)
	else
	    foldername="PatternTest_"$COUNTER"_"$(date +_%Y%m%d_%H%M%S)
	fi

        echo Creating $foldername

        mkdir -p "$foldername" 
        mv *png  "$foldername"
        cp templates/*Details.html "$foldername"
        mv *txt *log "$foldername"
   #     mv CTP7ToDigi.root "$foldername" 
        (cat templates/index_a ; echo RUN NUMBER: $RUN ;  cat templates/index_b) > index.html
        mv index.html "$foldername"
        
        mv CTP7DQM.root  "$foldername"
        rm *.root
        
        cp  "$foldername"/*png "$foldername"/index.html /afs/cern.ch/user/r/rctcmstr/www/    

        mv "$foldername" ../archive

   fi 
   let COUNTER+=1
done
    
