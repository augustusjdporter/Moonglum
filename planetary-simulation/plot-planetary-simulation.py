#currently just experimenting with python
#will extend to plot solar system graphs for each snapshot
#can then create gif on command line

import numpy as np
import matplotlib.pyplot as plt
from pylab import figure, axes, pie, title, show
import pylab as p

import scipy

i = 1
while i < 1461 :
	workfile = "Coords/It_" + `i` + ".txt"
#	print(workfile)

	x = np.loadtxt(workfile, usecols=range(1,2))
#	print "x"
#	print x
	y = np.loadtxt(workfile, usecols=range(2,3))
#	print "y"
#	print y
	z = np.loadtxt(workfile, usecols=range(3,4))
#	print "z"
#	print z

	plt.ylim([-2, 2])
	plt.xlim([-2, 2])
	plt.scatter(x, y, alpha=0.5)
	
	name ="Coords/PlotIt_" + str(i).zfill(5) +".pdf"

	#print name
	plt.savefig(name)
	plt.close()

	i = i + 1