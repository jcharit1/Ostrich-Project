#!/apps/anaconda/bin/python
# -*- coding: utf-8 -*-
"""
Created on Wed Oct  5 19:38:27 2016

@author: Jimmy Charite
"""
# Import functions
###############################################################################
import pandas as pd
import os

# Define needed functions
###############################################################################
def getInvestorPath(investor):
    cl=str(investor % 500)
    investor_path="/user/user1/jc4144/Nachum/Ostrich/cluster/cluster"
    investor_path=investor_path+cl+"/88808sample"+str(investor)+".txt"
    return investor_path

def getProgramPath(beta):
    program_path="/user/user1/jc4144/Nachum/Ostrich/code/bin/"
    if(beta==0):
        program_path=program_path+"ProgramOneFinalRSB0"
    else:
        program_path=program_path+"ProgramOneFinalRS"    
    return program_path
    
def getProgramCommand(investor,alpha,beta,gamma,delta,theta,tmax,partition,counter):
    investor_path=getInvestorPath(investor)
    program_path=getProgramPath(beta)
    str_command=program_path+' '+investor_path+' '
    str_command=str_command+'88808 504 set20161005Delta'+' ' 
    str_command=str_command+str(alpha)+' '+str(beta)+' '+str(gamma)+' '
    str_command=str_command+str(delta)+' '+str(theta)+' '+str(tmax)+' '
    str_command=str_command+str(partition)+' '+str(counter)+' '
    str_command=str_command+'RS 1000 0.001 0.001 CBS F T'
    head_com='/apps/wrappers/sge_run --grid_quiet --grid_submit=batch --grid_mem=10G "ulimit -c 0; '
    tail_com='"'    
    str_command=head_com+str_command+tail_com
    return str_command
    
def getInvestorList():
    investor_list_path='/user/user1/jc4144/Nachum/Ostrich/16forExpUtility1sampleID.txt'
    investor_list=pd.read_csv(investor_list_path,header=None)
    return investor_list

# get the parameter lists
###############################################################################
parameter_list_path='/user/user1/jc4144/Nachum/Ostrich/parameters/test20161005.txt'
parameter_list=pd.read_csv(parameter_list_path,header=None,delimiter=' ')
parameter_list=parameter_list.transpose()
parameter_list.columns=['alpha','beta','gamma','delta','theta','tmax','partition']

alphas=parameter_list[parameter_list.alpha.notnull()]['alpha']
betas=parameter_list[parameter_list.beta.notnull()]['beta']
gammas=parameter_list[parameter_list.gamma.notnull()]['gamma']
deltas=parameter_list[parameter_list.delta.notnull()]['delta']
thetas=parameter_list[parameter_list.theta.notnull()]['theta']
tmaxs=parameter_list[parameter_list.tmax.notnull()]['tmax']
partitions=parameter_list[parameter_list.partition.notnull()]['partition']

# get commands
###############################################################################
investor_list=getInvestorList()
investor_list.columns =['investor']

for inv in investor_list['investor']:
    counter=1
    for A in alphas:
        for B in betas:
            for G in gammas:
                for D in deltas:
                    for TH in thetas:
                        for TM in tmaxs:
                            for P in partitions:
                                str_command=getProgramCommand(inv,A,B,G,D,TH,TM,P,counter)
                                os.system(str_command)
                                counter=counter+1





