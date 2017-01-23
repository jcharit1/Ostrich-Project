#!/apps/anaconda/bin/python

# Load packages
########################################################################
import sys
import pandas as pd
import numpy as np

# Pull inputs
########################################################################
inv_list_path=str(sys.argv[1])
para_path=str(sys.argv[2])

# Upload inputs
########################################################################
inv_list=pd.read_csv(inv_list_path,header=None,index_col=None)
paras=pd.read_csv(para_path,header=None,index_col=None,sep=' ')

# Process
########################################################################
paras=paras.T
paras.columns=['alpha','beta','gamma','delta','theta','t_max','partition']
paras=np.sum(paras.notnull()).reset_index()
paras.columns=['paras','num']

expected_size=np.prod(paras.num)*len(inv_list)
print('Expected Number of Results: {:,}"'.format(expected_size))