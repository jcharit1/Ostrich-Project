#!/bin/bash
NAMEID=$1
SEARCHDIR=/NOBACKUP/scratch/jc4144/Nachum/Ostrich/cluster/
OUTFILE=/NOBACKUP/scratch/jc4144/Nachum/Ostrich/temp_file_list.txt

# Print a directory tree
find $SEARCHDIR > $OUTFILE

# Isolate files that I need
grep "$NAMEID" $OUTFILE > $OUTFILE

# Record number of files
NUMFILES=$(wc -l $OUTFILE)

# Loop over them and append to a new file
for FILE in `seq 1 $NUMFILES`;
do
	cat $FILE >> temp_agg_results_$NAMEID.txt
done
