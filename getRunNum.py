import os
print 'cern username',
x=raw_input()
print 'cern_password',
y=raw_input()
cmd="wget --no-check-certificate --user="+x+" --password="+y+" https://cmsdaq0.cern.ch/cmswbm/cmsdb/runSummary/RunSummary.html"
os.system("rm RunSummary.html")
os.system(cmd)
os.system("root -l -q lumi_RunSummary.C")

