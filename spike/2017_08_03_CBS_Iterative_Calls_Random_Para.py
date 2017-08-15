#!/apps/anaconda/bin/python

# Load packages
########################################################################
import os
import sys
import pandas as pd
from collections import deque

# Pull inputs
########################################################################
inv_list_path=str(sys.argv[1])
para_path=str(sys.argv[2])
current_results_path=str(sys.argv[3])
max_grid_jobs=int(str(sys.argv[4]))
max_ppt_use=float(str(sys.argv[5]))
name_main_program=str(sys.argv[6])

base_prog_path='/user/user1/jc4144/Nachum/Ostrich/code/bin/'

# Upload inputs
########################################################################
inv_list=pd.read_csv(inv_list_path,header=None,index_col=None)
paras=pd.read_csv(para_path,index_col=None)
current_results=pd.read_csv(current_results_path,header=None,index_col=None)

# Process
########################################################################
inv_list.columns=['investor']

current_results.columns=['investor','alpha','beta','gamma',
                         'delta','theta','partition','fit']

# Define Calls to Terminal
######################################################################## 
cmd_num_jimmy_jobs='echo $(($(qstat -u "jc4144" | wc -l)-2))'
cmd_num_all_jobs='echo $(($(qstat -u "*" | wc -l)-2))'

def get_job_nums(cmd_call):
    return max(int(os.popen(cmd_call).readlines()[0]),0)

def get_num_to_schedule(num_jimmy, num_all, max_grid_jobs,max_ppt_use):
    space_after_max=max(max_grid_jobs-num_all,0)
    grid_friendly_use=int(max_ppt_use*(num_all+space_after_max))-num_jimmy
    space_to_use=int(min(grid_friendly_use, space_after_max))
    space_to_use=max(space_to_use,0)
    return space_to_use

# Define Function to Get Program Name
########################################################################
def get_main_program_path(base_prog_path,name_main_program,beta):
    if(name_main_program=="ProgramOneFinal"):
        if(beta==0):
            return base_prog_path+'ProgramOneFinalRSB0'
        else:
            return base_prog_path+'ProgramOneFinalRS'
    if(name_main_program=="ProgramOneFinalAltUtility"):
        return base_prog_path+name_main_program        
                         
# Define Function Calls
########################################################################  
def run_simulation(investor,alpha,beta,gamma,delta,theta,t_max,partition,para_path,z):              
    
    #Defining the program path
    prog_path=get_main_program_path(base_prog_path,name_main_program,beta)
    
    #Defining the investor data path
    clu=str(int(investor % 500))
    investor=str(int(investor))
    z=str(int(z))    
    
    inv_data_path='/user/user1/jc4144/Nachum/Ostrich/cluster/cluster'+clu
    inv_data_path=inv_data_path+'/88808sample'+investor+'.txt'
    
    #Defining the parameter path
    para_file_name=para_path.split('/')[-1]
    para_file_name=para_file_name.split('.')[0]
    
    #Defining the full command
    command=prog_path+' '+inv_data_path+' 88808 504 '+para_file_name+' '
    command=command+str(alpha)+' '+str(beta)+' '+str(gamma)+' '+str(delta)+' '
    command=command+str(theta)+' '+str(t_max)+' '+str(round(partition))+' '
    command=command+z+' RS 100 0.001 0.001 CBS F T'
    
    #Defining prep command directory change
    dir_cd='cd /NOBACKUP/scratch/jc4144/Nachum/Ostrich/cluster/cluster'
    dir_cd=dir_cd+clu+"/thread"+z
    
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
all_results=inv_list[inv_list.investor.notnull()].copy()
all_results['key']=1
paras['key']=1  
all_results=pd.merge(all_results,paras,on='key')
del all_results['key']

all_results_cols=all_results.columns
							   
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

# Create command queue
########################################################################
queue=deque()
queue.extend(list(all_results.commands))
while(len(queue)>0):
    #get # of jobs to schedule
    num_jobs_to_schedule=get_num_to_schedule(get_job_nums(cmd_num_jimmy_jobs), 
                                             get_job_nums(cmd_num_all_jobs), 
                                             max_grid_jobs,
                                             max_ppt_use)
    #try scheduling them    
    for i in range(num_jobs_to_schedule):
        try:
            str_command=queue.pop()
            com_result=os.system(str_command)
            all_results.ix[all_results.commands==str_command,
                           'command_results']=com_result
        except IndexError:
            pass                 
            
#save the results file
temp=current_results_path.split('.')
all_results_path=temp[0]+"_iter_results."+temp[1]
all_results.to_csv(all_results_path, index=False)

