import sys
import numpy as np
import matplotlib.pyplot as plt
from shutil import copyfile
from math import log

filename = 'test_' + sys.argv[1]

def factors(n):
# 找出n的所有因数，作为盒子的边长
	return [i for i in range(1, n+1) if n % i == 0]

def init_data():
	data = np.loadtxt(filename, delimiter=",", dtype=int)
	length = data.shape[0]
	x = data[:, 0]
	y = data[:, 1]
	x -= min(x) # boxcounting是把左上角作为(0, 0)
	y -= min(y)
	return x, y, length

def boxcounting(x, y, length):
	x_r = []
	y_r = []
	N = []
	radius = min(max(x), max(y))
	radius = int(radius / 6) * 6
	# 这一步是微调radius,使得其约数尽可能多，这样后面得到的点也越多
	# 144的值是根据radius来选取的

	sizes = factors(radius) # 盒子列表
	for i in range(length):
		if x[i]<radius and y[i]<radius:
			x_r.append(x[i])
			y_r.append(y[i])

	bitmap = np.zeros((radius, radius), dtype=np.int)
	bitmap[x_r, y_r] = 1
	# 这里把在radius范围内的团簇转化为一个点阵

	for k in sizes:
		count = 0
		size = int(radius / k)
		for i in range(k):
			left = i * size
			right = (i + 1) * size
			for j in range(k):
				up = j * size
				down = (j + 1) * size
				patch = bitmap[up:down, left:right]
			    # 选取大点阵中的小块(即boxcounting核心步骤)
				if np.count_nonzero(patch) != 0:
					count += 1
		N.append(count)
	return sizes, N

def linear_fitting(sizes, N):
	logsizes = [log(i) for i in sizes]
	logN = [log(i) for i in N]
	A = np.vstack([logsizes, np.ones(len(logsizes))]).T
	k, b = np.linalg.lstsq(A, logN)[0]

	line = 'y=' + str(format(k, '0.4f')) + '*x' + '+' +  str(format(b, '0.4f'))
	plt.plot(logsizes, logN, 'o', label='original data', markersize=5)
	plt.plot(logsizes, [k * i + b for i in logsizes], 'r', label='fitting data'+line)
	plt.legend()

	plt.xlabel('ln(r)')
	plt.ylabel('ln(N)')
	plt.suptitle('the fractal dimension is ' + str(format(k,'0.4f')))

	# plt.show()
	plt.savefig('./boxcounting_' + sys.argv[1] + '.png')

x, y, length = init_data()
sizes, N = boxcounting(x, y, length)
linear_fitting(sizes, N)