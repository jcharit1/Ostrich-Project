#!/bin/bash

# script to delete all output
for clu in `seq 0 500`;
do
	/apps/wrappers/sge_run --grid_quiet --grid_submit=batch --grid_mem=300M "rm -rf /NOBACKUP/scratch/jc4144/Nachum/Ostrich/cluster/cluster$clu"
done

/apps/wrappers/sge_run --grid_quiet --grid_submit=batch --grid_mem=300M "rm -f /NOBACKUP/scratch/jc4144/Nachum/Ostrich/cluster/*.txt"

/apps/wrappers/sge_run --grid_quiet --grid_submit=batch --grid_mem=300M "rm -f /user/user1/jc4144/Nachum/Ostrich/AggOutput/*.txt"
