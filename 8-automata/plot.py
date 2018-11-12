import sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

N_FRAMES = 100
INTERVAL = 10

ratio = sys.argv[1]
def update(i):
    filename = 'test' + ratio + '/t_' + str(i)
    img = np.full((512, 512), 0, dtype=int)
    with open(filename) as f:
        lines = f.readlines()
        for line in lines:
            line = line.split(',')
            x = int(line[0])
            y = int(line[1])
            img[x, y] = 1
    plot.set_array(img)
    return plot,

fig = plt.figure()
img = np.full((512, 512), 0, dtype=int)
plot = plt.imshow(img, animated=True, cmap="gray", vmin = 0.2, vmax= 1.0, interpolation="bilinear", origin="lower")  
ani = FuncAnimation(
    fig=fig, func=update, 
    frames=np.arange(N_FRAMES), 
    interval=INTERVAL, blit=True)

plt.suptitle('initial ratio:' + ratio + '%')
# plt.show()
ani.save("up_" + ratio + ".gif", writer='imagemagick')