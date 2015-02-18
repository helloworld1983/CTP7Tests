#!/bin/bash
echo -n Username: 
read -s uname
# Read Password
echo -n Password: 
read -s psswd
echo
# Run Command
nohup python wgetRunNum.py $uname $psswd & 
