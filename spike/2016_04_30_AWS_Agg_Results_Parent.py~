#!/usr/bin/env python
import sys, glob, os
import pandas as pd

################################################################################
# Script to append the results
################################################################################

# Arguments
################################################################################
output_base_name = sys.argv[1] #base name of the output file
investor_list_path = sys.argv[2] #investor list path
sys_version = sys.argv[3]  


# Get path of program and output paths
################################################################################
sge = ""
program_path =""
out_path = ""
if sys_version == "AWSEBS":
	sge = 'qsub -N "Results" -o /dev/null -e /dev/null -V -b y -cwd'
	program_path = "/main/code/spike/2016_04_30_AWS_Agg_Results.py"
	out_path = "/investorOutput/"
if sys_version == "CBS":
	program_path = "/user/user1/jc4144/Nachum/Ostrich/code/spike/2016_04_30_AWS_Agg_Results.py"
if sys_version == "Personal":
	program_path = "/home/jim/Dropbox/Nachum/OstrichCPP/AWSCode/Ostrich/code/spike/2016_04_30_AWS_Agg_Results.py"

# get investor list and turn it into unique clusters
################################################################################
quotes = '"'

# read the list of investors, calculate the cluster, get unique list
investor_list = pd.read_csv(investor_list_path,header=None)
investor_list.columns = ['investors']
investor_list['investors']=(investor_list['investors'] % 500)
investor_list = investor_list.drop_duplicates()

# Loop through the clusters
for i, row in investor_list.iterrows():
	clu = investor_list['investors'][i]
	command = sge+" "+quotes+"python "+program_path+" "+str(output_base_name)+" "+str(clu)+" "+out_path+" "+str(sys_version)+quotes
	os.system(command)

