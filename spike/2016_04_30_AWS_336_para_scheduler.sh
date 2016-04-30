#!/bin/bash
PARASET=$1
JOBNAME=$2
MAXJOBQUEUE=$3
NINVESTOR=$4
FIRSTINTER=$5
MAXINTER=$6

## set secondary variables
QSUBOPTIONS="-o /dev/null -e /dev/null -V -b y -cwd"
EXECPROGRAM="/main/code/bin/ParentOstrich Simple /main/parameters/$PARASET.txt $PARASET 88808 504 1349P$NINTER $NINVESTOR RS 100 0.001 0.001 AWSEBS T F T"

## seed interations
NINTER=$FIRSTINTER

## launch first batch of jobs
qsub -N "ParentOstrich" $QSUBOPTIONS "ulimit -c 0; $EXECPROGRAM"

## update iterators
NINTER=$(($NINTER+1))

## loop through the remaining
while (( $(($NINTER<=$MAXINTER)) )); do
	NUMJOBS=$(qstat | grep -n "$JOBNAME" | wc -l);
	if (( $(($NUMJOBS<=$MAXJOBQUEUE)) && $((0==$(qstat | grep -n "ParentOstr" | wc -l))) )); then
		qsub -N "ParentOstrich" $QSUBOPTIONS "ulimit -c 0; $EXECPROGRAM";
		NINTER=$(($NINTER+1));
	fi
done

