import numpy as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('../TestsResults/Point6/HoareCenter.out', delimiter=' ')
x1, y1 = data1[:, 0], data1[:, 1]

data2 = np.loadtxt('../TestsResults/Point6/Shell.out', delimiter=' ')
x2, y2 = data2[:, 0], data2[:, 1]

plt.figure()
plt.plot(x1, y1, 'b-', label='Quick sort')
plt.plot(x2, y2, 'r-', label='Shell sort')

plt.xlabel('array size')
plt.ylabel('time')
plt.grid(True)
plt.legend()

plt.savefig('imgs/QuickVsShell.png')