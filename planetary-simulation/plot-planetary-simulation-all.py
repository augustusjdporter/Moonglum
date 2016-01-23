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


workfile_tr = "Coords/" + simDirectory + "/trajectories/Earth_trajectory.txt"
x_Earth = np.loadtxt(workfile_tr, usecols=range(0,1))
y_Earth = np.loadtxt(workfile_tr, usecols=range(1,2))
z_Earth = np.loadtxt(workfile_tr, usecols=range(2,3))


workfile_tr = "Coords/" + simDirectory + "/trajectories/Sun_trajectory.txt"
x_Sun = np.loadtxt(workfile_tr, usecols=range(0,1))
y_Sun = np.loadtxt(workfile_tr, usecols=range(1,2))
z_Sun = np.loadtxt(workfile_tr, usecols=range(2,3))

workfile_tr = "Coords/" + simDirectory + "/trajectories/Jupiter_trajectory.txt"
x_Jupiter = np.loadtxt(workfile_tr, usecols=range(0,1))
y_Jupiter = np.loadtxt(workfile_tr, usecols=range(1,2))
z_Jupiter = np.loadtxt(workfile_tr, usecols=range(2,3))


i = 1
while i < 1461 :
	workfile = "Coords/" + simDirectory + "/Snapshots/It_" + `i` + ".txt"
#	print(workfile)

	x = np.loadtxt(workfile, usecols=range(1,2))
	y = np.loadtxt(workfile, usecols=range(2,3))
	z = np.loadtxt(workfile, usecols=range(3,4))

	

	plt.ylim([-6, 6])
	plt.xlim([-6, 6])
	plt.scatter(x, y, alpha=0.5)
	plt.plot(x_Earth, y_Earth)
	plt.plot(x_Jupiter, y_Jupiter)
	plt.plot(x_Sun, y_Sun)
	
	name ="Coords/" + simDirectory + "/Plots/PlotIt_" + str(i).zfill(5) +".pdf"

	#print name
	plt.savefig(name)
	plt.close()

	i = i + 1