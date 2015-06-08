#!/bin/bash
 
NAME="runningL1A"
 
while [ "$1" != "" ]; do
    case $1 in
        -h | --help )               echo "harvesting.sh usage: bash harvesting.sh [-h] [--name dirName]"
                                    exit 1
                                    ;;
        --name )                    shift
                                    NAME=$1
                                    ;;
    esac
    shift
done
 
RUN=true
COUNTER=0
while [ $RUN == true ]; do

	if [ ! -d "$NAME" ]; 
	then
	  echo "Something bad happened: your directory with root files does not exit!"
	  echo "You should first run runCapture.sh; the harvesting will run in the background"
	else
	  cat "$NAME"/archiveList.txt  | xargs hadd -f L1ADQMMERGED.root 
	  root -b -q macros/fastplotter.C >& plots.log
	  root -b -q macros/linkplotter.C >& plots2.log 
	  mv L1ADQMMERGED.root "$NAME"
          mv *.png "$NAME" 
          mv plots*.log "$NAME"
          cp "$NAME"/*png index.html /afs/cern.ch/user/r/rctcmstr/www/L1A/
	fi

        let COUNTER+=1

	if [ "$COUNTER" -gt 100 ]; then
		RUN=false
		# Just a healthy check while I debug, running this 100 times is quite a lot of time
	fi	

        SERVICE='runCapture'

	if ps ax | grep -v grep | grep $SERVICE > /dev/null
	then
		    echo "$SERVICE capture script running, I will keep harvesting"
	else
		    echo "$SERVICE is not running"
		    RUN=false 	
	fi

	echo "I will sleep for 2 minutes"
	sleep 2m

done 
	
 
