#!/apps/anaconda/bin/python

# Load packages
########################################################################
import os
import sys
import pandas as pd

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
    
    
# Looping through the current results and running what is not there
########################################################################
for investor in inv_list[inv_list.investor.notnull()].investor:
    z=1
    for alpha in paras[paras.alpha.notnull()].alpha:
        for beta in paras[paras.beta.notnull()].beta:
            for gamma in paras[paras.gamma.notnull()].gamma:
                for delta in paras[paras.delta.notnull()].delta:
                    for theta in paras[paras.theta.notnull()].theta:
                        for t_max in paras[paras.t_max.notnull()].t_max:
                            for partition in paras[paras.partition.notnull()].partition:
                                z=z+1
                                n_results=len(current_results[(current_results.investor==investor) & 
                                                    (current_results.alpha==alpha) &
                                                    (current_results.beta==beta) &
                                                    (current_results.gamma==gamma) &
                                                    (current_results.delta==delta) &
                                                    (current_results.theta==theta) &
                                                    (current_results.partition==partition)])
                                if(n_results==0):
                                    command=run_simulation(investor,alpha,beta,
                                                           gamma,delta,theta,t_max,
                                                           partition,para_path,z%500)
                                    os.system(command)
                                    
