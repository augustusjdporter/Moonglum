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


workfile_tr = "Coords/" + simDirectory + "/trajectories/Sun_trajectory.txt"
x_Earth = np.loadtxt(workfile_tr, usecols=range(0,1))
y_Earth = np.loadtxt(workfile_tr, usecols=range(1,2))
z_Earth = np.loadtxt(workfile_tr, usecols=range(2,3))


#workfile_tr = "Coords/" + simDirectory + "/trajectories/Sun2_trajectory.txt"
#x_Sun = np.loadtxt(workfile_tr, usecols=range(0,1))
#y_Sun = np.loadtxt(workfile_tr, usecols=range(1,2))
#z_Sun = np.loadtxt(workfile_tr, usecols=range(2,3))

#workfile_tr = "Coords/" + simDirectory + "/trajectories/Jupiter_trajectory.txt"
#x_Jupiter = np.loadtxt(workfile_tr, usecols=range(0,1))
#y_Jupiter = np.loadtxt(workfile_tr, usecols=range(1,2))
#z_Jupiter = np.loadtxt(workfile_tr, usecols=range(2,3))

workfile = "Coords/" + simDirectory + "/Snapshots/It_" + plotCount + ".txt"
#	print(workfile)
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
#plt.scatter(x[names=="Sun2"], y[names=="Sun2"], marker="o", color='yellow')
#plt.scatter(x[names=="Earth"], y[names=="Earth"], marker="o", color='green')
#plt.scatter(x[names=="Jupiter"], y[names=="Jupiter"], marker="o", color='brown')
ax.plot(x_Earth, y_Earth, z_Earth, alpha=0.5)
#plt.plot(x_Jupiter, y_Jupiter, alpha=0.5)
#plt.plot(x_Sun, y_Sun, alpha=0.5)
	
name ="Coords/" + simDirectory + "/PlotIt3d_" + plotCount.zfill(5) +".pdf"

#print name
pyplot.show()
#Axes3D.close()
