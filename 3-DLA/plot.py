import sys
import numpy as np
import matplotlib.pyplot as plt

y = []
x = []

seq = sys.argv[1]

filename = 'test_' + seq
with open(filename) as f:
    lines = f.readlines()
    for line in lines:
        line = line.split(',')
        y.append(float(line[0]))
        x.append(float(line[1]))

plt.figure(figsize=(10,10))
plt.scatter(x, y, s=1, c=y, edgecolors='none')
plt.title("DLA", fontsize=14)
plt.tick_params(axis='both', labelsize=10)

# plt.show()
plt.savefig('dla_' + seq + '.png')