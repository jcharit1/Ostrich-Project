##################################################################################################
# Author: Jimmy Charité (jc4144@gsb.columbia.edu) 
# Code to test the fileExist fuction
##################################################################################################

#Libraries
##################################################################################################
library(devtools)
library(Rcpp)
library(Rcpp11)
library(data.table)
library(parallel)

#Directories and other prep
##################################################################################################
wkdir <- "/media/windows7/Users/Charite/Dropbox/Nachum/OstrichCPP/AWSCode/Ostrich/code/dev/Alternative_File_Exist_Function/"
setwd(wkdir)
codePath <- "file_exist_stat_rcpp.cpp"

coresAvailable <- detectCores()

#Compiling
##################################################################################################
attributes::sourceCpp(codePath,verbose = F)

#Files to check
##################################################################################################
#Fake file
fileExists("fake_file.txt")
#Closed real file
fileExists("closed_file.txt")
#Open real file
fileExists("open_file.txt")

