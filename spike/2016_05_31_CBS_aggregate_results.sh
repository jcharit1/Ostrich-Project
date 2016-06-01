#!/bin/bash
NAMEID=$1
MAXTHREADS=$2
SEARCHDIR=/NOBACKUP/scratch/jc4144/Nachum/Ostrich/cluster/
OUTFILE=/NOBACKUP/scratch/jc4144/Nachum/Ostrich/temp_file_list

# Print a directory tree
find $SEARCHDIR > $OUTFILE.txt

# Isolate files that I need
grep "$NAMEID" $OUTFILE.txt > $OUTFILE.txt

# Record number of files
NUMFILES=$(wc -l $OUTFILE.txt)

# Loop over them and append to a new file
for FILE in `seq 1 $MAXTHREADS`;
do
	cat $FILE >> $NAMEID.txt
done
