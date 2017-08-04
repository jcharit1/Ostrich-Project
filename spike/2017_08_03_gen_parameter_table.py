#!/apps/anaconda/bin/python

# Load packages
########################################################################
import sys
import pandas as pd
import numpy as np

# Pull inputs
########################################################################
num_paras=float(str(sys.argv[1]))
sim_seed=float(str(sys.argv[2]))
para_bounds_path=str(sys.argv[3])
para_table_path=str(sys.argv[4])

# Upload parameter bounds
########################################################################
tiny_mass=0.0000001
para_bounds=pd.read_csv(para_bounds_path,index_col=None)
para_bounds['max']=para_bounds['max']+tiny_mass

# Simulate data
########################################################################
np.random.seed(sim_seed)

para_table=pd.DataFrame()
para_table['alpha']=np.random.uniform(para_bounds[para_bounds.parameter=='alpha']['min'],
                                      para_bounds[para_bounds.parameter=='alpha']['max'],
                                      num_paras)
para_table['beta']=np.random.uniform(para_bounds[para_bounds.parameter=='beta']['min'],
                                      para_bounds[para_bounds.parameter=='beta']['max'],
                                      num_paras)
para_table['gamma']=np.random.uniform(para_bounds[para_bounds.parameter=='gamma']['min'],
                                      para_bounds[para_bounds.parameter=='gamma']['max'],
                                      num_paras)
para_table['delta']=np.random.uniform(para_bounds[para_bounds.parameter=='delta']['min'],
                                      para_bounds[para_bounds.parameter=='delta']['max'],
                                      num_paras)
para_table['theta']=np.random.uniform(para_bounds[para_bounds.parameter=='theta']['min'],
                                      para_bounds[para_bounds.parameter=='theta']['max'],
                                      num_paras)
para_table['t_max']=float(para_bounds[para_bounds.parameter=='t_max']['min'])
para_table['partition']=float(para_bounds[para_bounds.parameter=='partition']['min'])

# Save data
########################################################################
para_table.to_csv(para_table_path+'para_table'+'_n'+str(int(num_paras))+'_s'+str(int(sim_seed))+'.txt',index=False)
