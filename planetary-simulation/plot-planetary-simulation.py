#!/usr/bin/python

import sys

import numpy as np
import matplotlib.pyplot as plt
from pylab import figure, axes, pie, title, show
import pylab as p

import scipy

simDirectory = str(sys.argv[1])
plotCount = str(sys.argv[2])



workfile_tr = "Coords/" + simDirectory + "/trajectories/" + simDirectory + "_trajectories.txt"
traj_ID = np.loadtxt(workfile_tr, usecols=range(0,1))
x_traj = np.loadtxt(workfile_tr, usecols=range(1,2))
y_traj = np.loadtxt(workfile_tr, usecols=range(2,3))
z_traj = np.loadtxt(workfile_tr, usecols=range(3,4))

is_tracking_file = "Coords/" + simDirectory + "/trajectories/" + simDirectory + "_isTrackingTrajectories.txt"
tracking_list = np.loadtxt(is_tracking_file, usecols=range(0,1))

workfile = "Coords/" + simDirectory + "/Snapshots/It_" + plotCount + ".txt"
names = np.loadtxt(workfile, str, usecols=range(0,1))
x = np.loadtxt(workfile, usecols=range(1,2))
y = np.loadtxt(workfile, usecols=range(2,3))
z = np.loadtxt(workfile, usecols=range(3,4))

	

plt.ylim([-6, 6])
plt.xlim([-6, 6])
plt.scatter(x, y, alpha=0.75, marker=".", s=0.1)
plt.scatter(x[names=="Sun"], y[names=="Sun"], marker="o", color='yellow')
plt.scatter(x[names=="Earth"], y[names=="Earth"], marker="o", color='green')
for i, elem in enumerate(tracking_list):
	plt.plot(x_traj[traj_ID==elem], y_traj[traj_ID==elem], alpha=0.5)
	
name ="Coords/" + simDirectory + "/Plots/PlotIt_" + plotCount.zfill(5) +".pdf"

#print name
plt.savefig(name)
plt.close()