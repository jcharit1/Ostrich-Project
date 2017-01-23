#!/bin/bash

# script to aggregate all files in the data aggregation directory
/apps/wrappers/sge_run --grid_quiet --grid_submit=batch --grid_mem=500M "find /user/user1/jc4144/Nachum/Ostrich/AggOutput/ -name 'temp_*.txt' -exec cat {} + > /user/user1/jc4144/Nachum/Ostrich/AggOutput/agg_temp_results.txt"
