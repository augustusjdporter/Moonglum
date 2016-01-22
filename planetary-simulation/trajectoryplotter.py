#currently just experimenting with python
#will extend to plot solar system graphs for each snapshot
#can then create gif on command line
#hello

import numpy as np
import matplotlib.pyplot as plt
from pylab import figure, axes, pie, title, show
import pylab as p

import scipy

workfile_tr = "Earth_trajectory.txt"
x_tr = np.loadtxt(workfile_tr, usecols=range(0,1))
y_tr = np.loadtxt(workfile_tr, usecols=range(1,2))
z_tr = np.loadtxt(workfile_tr, usecols=range(2,3))

plt.ylim([-6, 6])
plt.xlim([-6, 6])
plt.plot(x_tr, y_tr)

workfile_tr = "Sun_trajectory.txt"
x_tr2 = np.loadtxt(workfile_tr, usecols=range(0,1))
y_tr2 = np.loadtxt(workfile_tr, usecols=range(1,2))
z_tr2 = np.loadtxt(workfile_tr, usecols=range(2,3))
plt.plot(x_tr2, y_tr2)

workfile_tr = "Jupiter_trajectory.txt"
x_tr3 = np.loadtxt(workfile_tr, usecols=range(0,1))
y_tr3 = np.loadtxt(workfile_tr, usecols=range(1,2))
z_tr3 = np.loadtxt(workfile_tr, usecols=range(2,3))
plt.plot(x_tr3, y_tr3)

plt.show()