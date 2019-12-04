'''
Created on Nov 17, 2011

@author: rupam

Invoke this with "python plot.py yourFileName"
'''
import sys
from numpy import *
from pylab import *
from mpl_toolkits.mplot3d import Axes3D

def main():
    x1steps = 41.0
    x2steps = 41.0
    x1range = linspace(2001, 1, x1steps)
    x2range = linspace(1, 2001, x2steps)
    y = loadtxt(sys.argv[1])

    fig = figure()
    ax = Axes3D(fig)
    x1,x2 = meshgrid(x1range,x2range)
    ax.plot_surface(x1, x2, y.T, cstride=1, rstride=1, cmap=cm.jet)
    ax.set_xlabel('ratio')
    ax.set_ylabel('size')
    ax.set_zlabel('difference')
    #savefig("plot.pdf", bbox_inches='tight')
    
if __name__ == '__main__':
    main()
    show()
