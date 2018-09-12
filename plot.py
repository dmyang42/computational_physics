import sys
import numpy as np
import scipy.signal as signal
import matplotlib.pyplot as plt

def deriv_map(x0, l0):
    return l0 * np.pi * np.cos(np.pi*x0)

def peak(x, l):
    x_array = np.array(x)
    l_array = np.array(l)
    peak_index = signal.argrelextrema(x_array,np.greater)
    print(l_array[peak_index])

def lyapunov (x, l, lambda_start, lambda_end, lambda_update):
    steps = round((lambda_end - lambda_start) / lambda_update)
    la = [lambda_start + i * lambda_update for i in range(steps)]
    ly = []

    i = 0
    deriv = [np.log(np.abs(deriv_map(x[i], l[i]))+1e-10) for i in range(len(x))]

    while i < (len(x) - 1):
        s = sum(deriv[i:i+200])
        ly.append(s)
        i = i + 200

    plt.figure(figsize=(10,6))
    plt.scatter(la, ly, s=5, edgecolors='none')

    plt.title("Lyapunov", fontsize=14)
    plt.xlim((lambda_start, lambda_end))
    plt.xlabel("$\lambda$", fontsize=12)
    plt.ylabel("$lyapunov$", fontsize=12)

    # x_ticks = np.arange(0.7198, 0.7200, 0.00002)
    # y_ticks = np.arange(-0.1, 0, 0.02)
    # plt.xticks(x_ticks)
    # plt.yticks(y_ticks)
    plt.tick_params(axis='both', labelsize=10)

    # plt.hlines(0, 0., 1, colors = "hellow", linestyles = "dashed")

    # plt.show()
    plt.savefig("test_lyapunov_"+test_seq+".png",dpi=1000)

    peak(ly, la)

def chaos (x, l, lambda_start, lambda_end):
    plt.figure(figsize=(10,6))
    plt.scatter(l, x, s=0.1, edgecolors='none')

    plt.title("Chaos", fontsize=14)
    plt.xlim((lambda_start, lambda_end))
    plt.xlabel("$\lambda$", fontsize=12)
    plt.ylabel("$x$", fontsize=12)
    plt.tick_params(axis='both', labelsize=10)

    # plt.show()
    plt.savefig("test_chaos_"+test_seq+".png",dpi=1000)

lambda_start = float(sys.argv[1])
lambda_end = float(sys.argv[2])
lambda_update = float(sys.argv[3])
test_seq = sys.argv[4]

filename = './test_' + test_seq

l = [] # lambda
x = [] # x

with open(filename) as f:
    lines = f.readlines()
    for line in lines:
        line = line.split(',')
        l.append(float(line[0]))
        x.append(float(line[1]))

lyapunov(x, l, lambda_start, lambda_end, lambda_update)
chaos(x, l, lambda_start, lambda_end)
