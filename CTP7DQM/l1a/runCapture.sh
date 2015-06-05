#!/bin/bash

NAME="runningL1A"
N_ITERATIONS=1

while [ "$1" != "" ]; do
    case $1 in
        -h | --help )               echo "runContinuous.sh usage: bash runContinuous.sh [-h] [--name dirName] [n_iterations]"
                                    exit 1
                                    ;;
        --name )                    shift
                                    NAME=$1
                                    ;;
        * )                         N_ITERATIONS=$1
                                    ;;
    esac
    shift
done

if [ -d "$NAME" ]; then
  # Control will enter here if $DIRECTORY exists.
  echo "Directory name already in use: renaming it for archiving purposes"
  reName=$NAME"_old"
  mv "$NAME" "$reName"
fi

mkdir "$NAME"

touch "$NAME"/archiveList.txt

COUNTER=1
until [  $COUNTER -gt "$N_ITERATIONS" ]; do
	if [ $(( $COUNTER % 10 )) -eq 0 ] ; then
		echo "Running Capture Number...." $COUNTER
	fi

        cmsRun RCTToDigi_cfg.py   >& rct.log
        cmsRun L1ADQM_cfg.py   >& dqm.log

        timestamp=$(date +%Y%m%d_%H%M%S)
	foldername=$COUNTER"_Capture_"$timestamp
	mkdir -p "$NAME/$foldername" 

	mv *.root "$NAME/$foldername"
	mv *.log "$NAME/$foldername"

	echo -e $NAME/$COUNTER"_Capture_"$timestamp"/L1ADQM.root" >> "$NAME"/archiveList.txt 

	let COUNTER+=1

        SERVICE='runHarvesting'

        if ps ax | grep -v grep | grep $SERVICE > /dev/null
        then
                    echo "$SERVICE running"
        else
		    echo "Harvesting not running, restarting..."	
		    sh ./runHarvesting.sh --name $NAME >& "$NAME"/logHarvesting.txt &	 	
        fi




	done


NUMOFLINES=$(wc -l "$NAME"/archiveList.txt)
echo $NUMOFLINES" processed captures"

