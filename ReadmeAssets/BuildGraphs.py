import numpy as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('../TestsResults/Point8/LSD.out', delimiter=' ')
x1, y1 = data1[:, 0], data1[:, 1]

data2 = np.loadtxt('../TestsResults/Point8/MSD.out', delimiter=' ')
x2, y2 = data2[:, 0], data2[:, 1]

#data3 = np.loadtxt('../TestsResults/Point5/HoareMedian3.out', delimiter=' ')
#x3, y3 = data3[:, 0], data3[:, 1]

#data4 = np.loadtxt('../TestsResults/Point5/HoareMedianRnd3.out', delimiter=' ')
#x4, y4 = data4[:, 0], data4[:, 1]

plt.figure()
plt.plot(x1, y1, 'b-', label='LSD')
plt.plot(x2, y2, 'r-', label='MSD')
#plt.plot(x3, y3, 'g-', label='median 3 pivot')
#plt.plot(x4, y4, 'm-', label='median 3 rnd pivot')

plt.xlabel('array size')
plt.ylabel('time')
plt.grid(True)
plt.legend()

plt.savefig('imgs/DigitsSorts.png')