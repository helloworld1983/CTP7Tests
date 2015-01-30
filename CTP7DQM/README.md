TestDQM
=======

First attempt at monitoring 

a) Install
----------

```bash
scram pro -n dqmTests CMSSW CMSSW_7_3_0_pre2
cd dqmTests/src
#Setup your CMSSW environment
cmsenv
#You might want to run this before doing ANYTHING else in src:
git cms-init
#Download the CTP7ToDigi package:
git clone --recursive https://github.com/uwcms/CTP7ToDigi.git CTP7Tests/CTP7ToDigi
#Download the DQM modules (different folder to facilitate potential integration with the official DQM one day):
git clone --recursive https://github.com/mcepeda/TestDQM.git CTP7Tests/CTP7DQM
scramv1 -j 8   
```

b) Run
------

Running is split in three sequences now (capture - dqm - plot), using  CTP7ToDigi_cfg.py and  CTP7DQM_cfg.py plus finally a preliminary plotting macro (fastplotter)
that will evolve to a executable.

```bash
cd test
#b1) for running capture and then DQM 
# (for this step you need to have the forwarding from the ctp7 active, and coordinate with the crew in P5
# to make sure you can play)
bash runCaptureDQMPlot.sh
#b2) for running only the DQM - plotting sequence
# (this assumes you already saved a CTP7ToDigi.root file with the captured information 
# on a previous run of CTP7ToDigi_cfg.py - you will just be plotting the results)
bash runDQMPlot.sh
```




  
