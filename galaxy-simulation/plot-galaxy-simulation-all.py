#currently just experimenting with python
#will extend to plot solar system graphs for each snapshot
#can then create gif on command line
#hello

#!/usr/bin/python

import sys

import numpy as np
import matplotlib.pyplot as plt
from pylab import figure, axes, pie, title, show
import pylab as p

import scipy

simDirectory = str(sys.argv[1])


i = 1
while i < 1461 :
	workfile = "Coords/" + simDirectory + "/Snapshots/It_" + `i` + ".txt"
#	print(workfile)

	x = np.loadtxt(workfile, usecols=range(1,2))
	y = np.loadtxt(workfile, usecols=range(2,3))
	z = np.loadtxt(workfile, usecols=range(3,4))

	

	plt.ylim([-20, 20])
	plt.xlim([-20, 20])
	plt.scatter(x, y, alpha=0.75, marker="o", s=1)
	
	name ="Coords/" + simDirectory + "/Plots/PlotItzoomout_" + str(i).zfill(5) +".pdf"

	#print name
	plt.savefig(name)
	plt.close()

	i = i + 1