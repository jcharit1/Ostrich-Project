#!/apps/anaconda/bin/python
import sys,os,fnmatch

# Base name of the output file
########################################################################
oname = str(sys.argv[1])
cluster_name = str(sys.argv[2])
bdir='/NOBACKUP/scratch/jc4144/Nachum/Ostrich/cluster/cluster'+cluster_name
bdir=bdir+'/'

outFile='/user/user1/jc4144/Nachum/Ostrich/AggOutput/clu'
outFile=outFile+cluster_name+oname

# find and aggregate them into one file
########################################################################
strMatch="*"+oname+"*"
with open(outFile, "w") as fo:
	for dirpath,dirnames,filenames in os.walk(bdir):
		for files in filenames:
			if (fnmatch.fnmatch(files,strMatch)):
				f = os.path.join(dirpath,files)
				with open(f,'r') as fi: fo.write(fi.read())

