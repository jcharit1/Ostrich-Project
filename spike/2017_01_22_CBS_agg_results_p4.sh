#!/bin/bash

# script create the directory tree
/apps/wrappers/sge_run --grid_quiet --grid_submit=batch --grid_mem=300M "cd /NOBACKUP/scratch/jc4144/Nachum/Ostrich/cluster; mkdir -p cluster{0..500}/thread{0..500}"
