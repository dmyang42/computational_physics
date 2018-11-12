import sys
import matplotlib.pyplot as plt

ratio = sys.argv[1]
filename = 'count_' + ratio

x = range(10000)
y = []
with open(filename) as f:
    lines = f.readlines()
    for line in lines:
        line = line.split()
        y.append(float(line[0]) / (512 * 512))

plt.plot(x, y)
# plt.show()
plt.savefig(filename + '.png')