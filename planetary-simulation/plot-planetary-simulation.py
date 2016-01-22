#currently just experimenting with python
#will extend to plot solar system graphs for each snapshot
#can then create gif on command line
#hello

import numpy as np
import matplotlib.pyplot as plt
from pylab import figure, axes, pie, title, show
import pylab as p

import scipy

simDirectory = raw_input("Which simulation shall we plot?")


workfile_tr = "Coords/Earth_trajectory.txt"
x_tr = np.loadtxt(workfile_tr, usecols=range(0,1))
y_tr = np.loadtxt(workfile_tr, usecols=range(1,2))
z_tr = np.loadtxt(workfile_tr, usecols=range(2,3))
i = 1
while i < 1461 :
	workfile = "Coords/It_" + `i` + ".txt"
#	print(workfile)

	x = np.loadtxt(workfile, usecols=range(1,2))
	y = np.loadtxt(workfile, usecols=range(2,3))
	z = np.loadtxt(workfile, usecols=range(3,4))

	

	plt.ylim([-6, 6])
	plt.xlim([-6, 6])
	plt.scatter(x, y, alpha=0.5)
	plt.plot(x_tr, y_tr)
	
	name ="Coords/PlotIt_" + str(i).zfill(5) +".pdf"

	#print name
	plt.savefig(name)
	plt.close()

	i = i + 1