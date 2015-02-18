import sys
import os
import time
from sys import argv
uname=argv[1]
passw=argv[2]
cmd="wget --no-check-certificate --user="+uname+" --password="+passw+" https://cmsdaq0.cern.ch/cmswbm/cmsdb/runSummary/RunSummary.html"
while True:
    os.system("rm RunSummary.html")
    os.system(cmd)
    time.sleep(60) 
