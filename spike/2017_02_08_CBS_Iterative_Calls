#!/apps/anaconda/bin/python

# Load packages
########################################################################
import os
import sys
import pandas as pd
from itertools import product

# Pull inputs
########################################################################
inv_list_path=str(sys.argv[1])
para_path=str(sys.argv[2])
current_results_path=str(sys.argv[3])

# Upload inputs
########################################################################
inv_list=pd.read_csv(inv_list_path,header=None,index_col=None)
paras=pd.read_csv(para_path,header=None,index_col=None,sep=' ')
current_results=pd.read_csv(current_results_path,header=None,index_col=None)

# Process
########################################################################
inv_list.columns=['investor']

paras=paras.T
paras.columns=['alpha','beta','gamma','delta','theta','t_max','partition']

current_results.columns=['investor','alpha','beta','gamma',
                         'delta','theta','partition','fit']
                         
# Define Function Calls
########################################################################  
def run_simulation(investor,alpha,beta,gamma,delta,theta,t_max,partition,
                   para_path,z):              
    
    #Defining the program path
    prog_path='/user/user1/jc4144/Nachum/Ostrich/code/bin/'
    if(beta==0):
        prog_path=prog_path+'ProgramOneFinalRSB0'
    else:
        prog_path=prog_path+'ProgramOneFinalRS'
    
    #Defining the investor data path
    clu=str(investor % 500)
    inv_data_path='/user/user1/jc4144/Nachum/Ostrich/cluster/cluster'+str(clu)
    inv_data_path=inv_data_path+'/88808sample'+str(round(investor))+'.txt'
    
    #Defining the parameter path
    para_file_name=para_path.split('/')[-1]
    para_file_name=para_file_name.split('.')[0]
    
    #Defining the full command
    command=prog_path+' '+inv_data_path+' 88808 504 '+para_file_name+' '
    command=command+str(alpha)+' '+str(beta)+' '+str(gamma)+' '+str(delta)+' '
    command=command+str(theta)+' '+str(t_max)+' '+str(round(partition))+' '
    command=command+str(z)+' RS 100 0.001 0.001 CBS F T'
    
    #Defining prep command directory change
    dir_cd='cd /NOBACKUP/scratch/jc4144/Nachum/Ostrich/cluster/cluster'
    dir_cd=dir_cd+clu+"/thread"+str(z)
    
    #Defining the SGE command before command
    sge='/apps/wrappers/sge_run --grid_submit=batch --grid_mem=2G'
    
    #special
    sp_com='ulimit -c 0'
    
    #Other
    qs='"'
    sc=';'
    s=' '
    
    command=dir_cd+sc+sge+s+qs+sp_com+sc+command+qs
    
    return command
    
# Creating the set of all possible combinations
########################################################################
all_results_cols=['investor']
all_results_cols.extend(paras.columns)
all_results =pd.DataFrame(list(product(inv_list[inv_list.investor.notnull()].investor,
                                       paras[paras.alpha.notnull()].alpha,
                                       paras[paras.beta.notnull()].beta,
									   paras[paras.gamma.notnull()].gamma,
									   paras[paras.delta.notnull()].delta,
									   paras[paras.theta.notnull()].theta,
									   paras[paras.t_max.notnull()].t_max,
									   paras[paras.partition.notnull()].partition)),
									   columns=all_results_cols)
							   
# adding current results flag
########################################################################
current_results['done']=1
merge_on=['investor','alpha','beta','gamma','delta','theta','partition']
all_results=pd.merge(all_results,current_results,how='left',on=merge_on)

all_results=all_results[all_results.done.isnull()].copy()

# Looping through the current results and running what is not there
########################################################################
t_max=paras[paras.t_max.notnull()].t_max[0]
all_results['z']=range(0+1,len(all_results)+1)

#round the results
all_results['investor']=all_results['investor'].round(0)
all_results['alpha']=all_results['alpha'].round(1)
all_results['beta']=all_results['beta'].round(1)
all_results['gamma']=all_results['gamma'].round(1)
all_results['delta']=all_results['delta'].round(1)
all_results['theta']=all_results['theta'].round(1)
all_results['partition']=all_results['partition'].round(0)

# wrapper function to allow 
def get_commands(row):
	result=run_simulation(row['investor'],
	                      row['alpha'],
						  row['beta'],
                          row['gamma'],
						  row['delta'],
						  row['theta'],
						  t_max,
						  row['partition'],
						  para_path,
						  row['z']%500)
	return result
						  
all_results['commands']=all_results.apply(get_commands, axis=1)

#apply command
all_results['command_results']=[os.system(s) for s in all_results.command]

#save the results file
temp=current_results_path.split('.')
all_results_path=temp[0]+"_iter_results."+temp[1]
all_results.to_csv(all_results_path, index=False)

