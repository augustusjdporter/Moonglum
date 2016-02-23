#currently just experimenting with python
#will extend to plot solar system graphs for each snapshot
#can then create gif on command line
#hello

#!/usr/bin/python

import sys

import numpy as np
from matplotlib import pyplot
import pylab
from mpl_toolkits.mplot3d import Axes3D
fig = pylab.figure()
ax = Axes3D(fig)

from pylab import figure, axes, pie, title, show
import pylab as p

import scipy

simDirectory = str(sys.argv[1])
plotCount = str(sys.argv[2])


workfile_tr = "planetary-simulation/Coords/" + simDirectory + "/trajectories/" + simDirectory + "_trajectories.txt"
traj_ID = np.loadtxt(workfile_tr, usecols=range(0,1))
x_traj = np.loadtxt(workfile_tr, usecols=range(1,2))
y_traj = np.loadtxt(workfile_tr, usecols=range(2,3))
z_traj = np.loadtxt(workfile_tr, usecols=range(3,4))

is_tracking_file = "planetary-simulation/Coords/" + simDirectory + "/trajectories/" + simDirectory + "_isTrackingTrajectories.txt"
tracking_list = np.loadtxt(is_tracking_file, usecols=range(0,1))

workfile = "planetary-simulation/Coords/" + simDirectory + "/Snapshots/It_" + plotCount + ".txt"
names = np.loadtxt(workfile, str, usecols=range(0,1))
x = np.loadtxt(workfile, usecols=range(1,2))
y = np.loadtxt(workfile, usecols=range(2,3))
z = np.loadtxt(workfile, usecols=range(3,4))


	
z[z>6]= np.nan
z[z<-6]= np.nan

x[x>6]= np.nan
x[x<-6]= np.nan

y[y>6]= np.nan
y[y<-6]= np.nan

ax.set_xlim3d([-6, 6])
ax.set_ylim3d([-6, 6])
ax.set_zlim3d([-6, 6])
ax.scatter(x, y, z, alpha=0.75, marker=".", s=1)
ax.scatter(x[names=="Sun"], y[names=="Sun"], z[names=="Sun"], marker="o", color='yellow')
ax.scatter(x[names=="Star"], y[names=="Star"], z[names=="Star"], marker="o", color='yellow')
ax.scatter(x[names=="Earth"], y[names=="Earth"], z[names=="Earth"], marker="o", color='green')
ax.scatter(x[names=="Jupiter"], y[names=="Jupiter"], z[names=="Jupiter"], marker="o", color='orange')

for i, elem in enumerate(tracking_list):
	ax.plot(x_traj[traj_ID==elem], y_traj[traj_ID==elem], z_traj[traj_ID==elem], alpha=0.5)
	
name ="Coords/" + simDirectory + "/PlotIt3d_" + plotCount.zfill(5) +".pdf"

#print name
pyplot.show()
#Axes3D.close()
