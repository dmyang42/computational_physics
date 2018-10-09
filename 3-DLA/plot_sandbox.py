import sys
import numpy as np
import matplotlib.pyplot as plt
from shutil import copyfile
from math import log

filename = 'test_' + sys.argv[1]

def init_data():
# 将坐标数据转化为偏离中心距离的数据
	data = np.loadtxt(filename, delimiter=",", dtype=int)
	length = data.shape[0]
	x = data[:, 0]
	y = data[:, 1]
	center = x[0]  
	x -= center # sandbox是把凝聚中心作为(0, 0)
	y -= center		
	return x, y, length

def sandbox(x, y, length):
# 输出化sandbox列表，即以radius为最大sandbox，以interval为间隔产生一组盒子
	radius = min(map(abs, [max(x), min(x), max(y), min(y)]))
	interval = int(radius / 30)
	r = range(radius)[::interval]
	N = [0]
	for i in range(len(r)-1):
		count = 0
		for j in range(length):
			if max(abs(x[j]), abs(y[j])) < r[i+1]:
				count += 1
		N.append(count)
	return r, N

def linear_fitting(r, N):
# 线性拟合logr,logN 并绘图
	logr = [log(i) for i in r[1:]]
	logN = [log(i) for i in N[1:]]
	A = np.vstack([logr, np.ones(len(logr))]).T
	k, b = np.linalg.lstsq(A, logN)[0]

	line = 'y=' + str(format(k, '0.4f')) + '*x' + '+' +  str(format(b, '0.4f'))
	plt.plot(logr, logN, 'o', label='original data', markersize=5)
	plt.plot(logr, [k * i + b for i in logr], 'r', label='fitting data'+line)
	plt.legend()

	plt.xlabel('ln(r)')
	plt.ylabel('ln(N)')
	plt.suptitle('fractal dimension : ' + str(format(k,'0.4f')))

	# plt.show()
	plt.savefig('./sandbox_' + sys.argv[1] +'.png')
	
x, y, length = init_data()
r, N = sandbox(x, y, length)
linear_fitting(r, N)