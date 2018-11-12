import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

x = []
y = []
z = [] 
num = sys.argv[1]
filename = './test_' + num

with open(filename) as f:
    lines = f.readlines()
    for line in lines:
        line = line.split(',')
        x.append(float(line[0]))
        y.append(float(line[1]))
        
plt.figure(figsize=(6,6))
plt.scatter(x, y, s=1)
# plt.show()
plt.savefig("2d_" + num + ".png")
