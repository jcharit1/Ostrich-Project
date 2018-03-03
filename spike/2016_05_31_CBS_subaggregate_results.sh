#!/bin/bash
SUBOUTFILEPATH=$1
TH=$2
OUTDIR=$3
OUTFILE=thread$TH.txt

while read outfile; do 
    cat $outfile >> $OUTDIR$OUTFILE
done < $SUBOUTFILEPATH
