#!/bin/bash
NAMEID=$1
MAXTHREADS=$2
SEARCHDIR=/NOBACKUP/scratch/jc4144/Nachum/Ostrich/cluster/
OUTDIR=/NOBACKUP/scratch/jc4144/Nachum/Ostrich/
OUTFILE=temp_file_list
SUBOUTFILE=temp_file_list_thread
SUBSCRIPT=/user/user1/jc4144/Nachum/Ostrich/code/spike/2016_05_31_CBS_subaggregate_results.sh

# Print a directory tree
find $SEARCHDIR > $OUTDIR$OUTFILE.txt

# Loop over them and append to a new file
for TH in `seq 1 $MAXTHREADS`;
do
	#creating a separate file for each "thread" folder under "cluster/cluster{0...500}/thread{0...500}/"
	grep "$NAMEID" $OUTDIR$OUTFILE.txt | grep "thread$TH/" > $OUTDIR$SUBOUTFILE$TH.txt

	#calling another script to aggregate temp_file_list_thread$TH.txt
	/apps/wrappers/sge_run --grid_quiet --grid_submit=batch --grid_mem=300M "sh $SUBSCRIPT $OUTDIR$SUBOUTFILE$TH.txt $TH $OUTDIR"
done
