#currently just experimenting with python
#will extend to plot solar system graphs for each snapshot
#can then create gif on command line
#hello test part 2 heloooo

#!/usr/bin/python

import sys

import matplotlib
# Force matplotlib to not use any Xwindows backend.
matplotlib.use('Agg')

import numpy as np
import matplotlib.pyplot as plt
from pylab import figure, axes, pie, title, show
import pylab as p

import scipy

simDirectory = "LongRun"


workfile_tr = "Coords/" + simDirectory + "/trajectories/" + simDirectory + "_trajectories.txt"
traj_ID = np.loadtxt(workfile_tr, usecols=range(0,1))
x_traj = np.loadtxt(workfile_tr, usecols=range(1,2))
y_traj = np.loadtxt(workfile_tr, usecols=range(2,3))
z_traj = np.loadtxt(workfile_tr, usecols=range(3,4))

is_tracking_file = "Coords/" + simDirectory + "/trajectories/" + simDirectory + "_isTrackingTrajectories.txt"
tracking_list = np.loadtxt(is_tracking_file, usecols=range(0,1))


#i = 1
for num in range  (0,1000):
	#workfile = "Coords/" + simDirectory + "/Snapshots/It_" + `i` + ".txt"
#	

	workfile = "Coords/" + simDirectory + "/Snapshots/It_" + str(num*30 +1) + ".txt"
	print(workfile)
	names = np.loadtxt(workfile, str, usecols=range(0,1))
	x = np.loadtxt(workfile, usecols=range(1,2))
	y = np.loadtxt(workfile, usecols=range(2,3))
	z = np.loadtxt(workfile, usecols=range(3,4))

		
	plot_lim = 15
	plt.ylim([-15, 15])
	plt.xlim([-15, 15])
	plt.scatter(x, y, alpha=0.75, marker=".", color='purple', s=0.1)
	plt.scatter(x[names=="Sun"], y[names=="Sun"], color='yellow')
	plt.scatter(x[names=="Star"], y[names=="Star"], color='yellow')
	plt.scatter(x[names=="Earth"], y[names=="Earth"], color='green')
	plt.scatter(x[names=="Jupiter"], y[names=="Jupiter"], marker="o", color='orange')
	for i, elem in enumerate(tracking_list):
		plt.plot(x_traj[traj_ID==elem], y_traj[traj_ID==elem], alpha=0.5)
		
	name ="Coords/" + simDirectory + "/Plots/PlotIt_" + str(num).zfill(5) +".png"

	#i = i + 30

	ax = plt.subplot()
	ax.set_axis_bgcolor('black')
	ax.set_axis_bgcolor((0, 0, 0))

	plt.savefig(name)
#	plt.show()
	plt.close()
	print ("Plot ", name, " finished!")

	
