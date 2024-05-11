import numpy as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('../TestsResults/BinaryHeap/Linear.out', delimiter=' ')
x1, y1 = data1[:, 0], data1[:, 1]

data2 = np.loadtxt('../TestsResults/BinaryHeap/Inserts.out', delimiter=' ')
x2, y2 = data2[:, 0], data2[:, 1]

plt.figure()
plt.plot(x1, y1, 'b-', label='Linear inserts')
plt.plot(x2, y2, 'r-', label='Std inserts')

plt.xlabel('array size')
plt.ylabel('time')
plt.grid(True)
plt.legend()

plt.savefig('imgs/BinaryHeap.png')