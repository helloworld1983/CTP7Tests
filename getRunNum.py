import os
import getpass
print 'cern username',
x=raw_input()
y=getpass.getpass('cern afs password')
cmd="wget --no-check-certificate --user="+x+" --password="+y+" https://cmsdaq0.cern.ch/cmswbm/cmsdb/runSummary/RunSummary.html"
os.system("rm RunSummary.html")
os.system(cmd)
os.system("root -l -q lumi_RunSummary.C")

