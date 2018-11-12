import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

x = []
y = []
z = [] 
num = sys.argv[1]
elev = int(sys.argv[2])
azim = int(sys.argv[3])
filename = './test_' + num

with open(filename) as f:
    lines = f.readlines()
    for line in lines:
        line = line.split(',')
        x.append(float(line[0]))
        y.append(float(line[1]))
        z.append(float(line[2]))

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_aspect('equal')
ax.scatter(x, y, z, c=x, s=1)
ax.view_init(elev=elev, azim=azim)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
# plt.show()
plt.savefig("test_" + num + ".png")