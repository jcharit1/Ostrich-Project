#!/usr/bin/env python
import sys, glob, os
import pandas as pd

################################################################################
# Script to append the results
################################################################################

# Arguments
################################################################################
output_base_name = sys.argv[1] #base name of the output file
clu = sys.argv[2] #file path
out_path = sys.argv[3] #where to dump the 
sys_version = sys.argv[4] #where to dump the 


# Aggregating the data
################################################################################

# get the file path
directory_path =""
if sys_version == "AWSEBS":
	directory_path = "/investorOutput/cluster/cluster"+str(clu)+"/"
if sys_version == "CBS":
	directory_path = "/NOBACKUP/scratch/jc4144/Nachum/Ostrich/cluster/cluster"+str(clu)+"/"
if sys_version == "Personal":
	directory_path = "/media/windows7/Users/Charite/Dropbox/Nachum/OstrichCPP/AWSCode/Ostrich/investorOutput/cluster/cluster"+str(clu)+"/"

# Get all the file names
all_results = glob.glob(os.path.join(directory_path, "thread*/*"+output_base_name+"*.txt")) 


# Put them all in a data frame
df = pd.concat((pd.read_csv(f,header=None) for f in all_results))

# Output path
out_path = out_path+clu+"_"+output_base_name+".txt"

# Output results
df.to_csv(out_path, header=None)
