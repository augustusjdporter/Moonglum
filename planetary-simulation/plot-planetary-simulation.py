#!/usr/bin/python

import sys

import matplotlib
# Force matplotlib to not use any Xwindows backend.
#matplotlib.use('Agg')

import numpy as np
import matplotlib.pyplot as plt

from pylab import figure, axes, pie, title, show
import pylab as p

import scipy

simDirectory = str(sys.argv[1])
coordCount = str(sys.argv[2])
plotCount = str(sys.argv[3])



workfile_tr = "planetary-simulation/Coords/" + simDirectory + "/trajectories/" + simDirectory + "_trajectories.txt"
traj_ID = np.loadtxt(workfile_tr, usecols=range(0,1))
x_traj = np.loadtxt(workfile_tr, usecols=range(1,2))
y_traj = np.loadtxt(workfile_tr, usecols=range(2,3))
z_traj = np.loadtxt(workfile_tr, usecols=range(3,4))

is_tracking_file = "planetary-simulation/Coords/" + simDirectory + "/trajectories/" + simDirectory + "_isTrackingTrajectories.txt"
tracking_list = np.loadtxt(is_tracking_file, usecols=range(0,1))

workfile = "planetary-simulation/Coords/" + simDirectory + "/Snapshots/It_" + coordCount + ".txt"
names = np.loadtxt(workfile, str, usecols=range(0,1))
x = np.loadtxt(workfile, usecols=range(1,2))
y = np.loadtxt(workfile, usecols=range(2,3))
z = np.loadtxt(workfile, usecols=range(3,4))

	
plot_lim = 15
plt.ylim([-15, 15])
plt.xlim([-15, 15])
plt.scatter(x, y, alpha=0.75, marker=".", color='purple', s=0.1)
plt.scatter(x[names=="Sun"], y[names=="Sun"], color='yellow', s=100)
plt.scatter(x[names=="Star"], y[names=="Star"], color='yellow', s=100)
plt.scatter(x[names=="Earth"], y[names=="Earth"], color='green', s=100)
plt.scatter(x[names=="Jupiter"], y[names=="Jupiter"], marker="o", color='orange')
#for i, elem in enumerate(tracking_list):
#	plt.plot(x_traj[traj_ID==elem], y_traj[traj_ID==elem], alpha=0.5)
	
name ="planetary-simulation/Coords/" + simDirectory + "/Plots/PlotIt_" + plotCount.zfill(5) +".png"

ax = plt.subplot()
ax.set_axis_bgcolor('black')
ax.set_axis_bgcolor((0, 0, 0))

plt.savefig(name)
#plt.show()
plt.close()
print ("Plot ", name, " finished!")