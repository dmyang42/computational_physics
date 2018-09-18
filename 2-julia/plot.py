import sys
import numpy as np
import matplotlib.pyplot as plt

x = []
y = []
x_0 = sys.argv[1]
y_0 = sys.argv[2]
num = sys.argv[3]
filename = './test_' + x_0 + '_' + y_0 + '_' + num

with open(filename) as f:
    lines = f.readlines()
    for line in lines:
        line = line.split(',')
        x.append(float(line[0]))
        y.append(float(line[1]))

plt.figure(figsize=(10,10))
plt.title('x=' + x_0 + ',' + 'y=' + y_0 + ',' + 'num=' + num)
plt.xlim((-2, 2))
plt.ylim((-2, 2))
plt.scatter(x, y, s=0.1, c=(0,0,0), edgecolors='none')

# plt.show()
plt.savefig(filename + '.png', dpi=1000)