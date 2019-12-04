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
    sizeBegin=1401
    sizeEnd=1801
    sizeStep=1
    ratioBegin=1
    ratioEnd=2001
    ratioStep=400
    x1steps = (ratioEnd-ratioBegin)/ratioStep+1
    x2steps = (sizeEnd-sizeBegin)/sizeStep+1
    x1range = linspace(ratioEnd, ratioBegin, x1steps)
    x2range = linspace(sizeBegin, sizeEnd, x2steps)
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
