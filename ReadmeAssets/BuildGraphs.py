import numpy as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('../TestsResults/Point9/HeapSort.out', delimiter=' ')
x1, y1 = data1[:, 0], data1[:, 1]

data2 = np.loadtxt('../TestsResults/Point9/Hoare_Central.out', delimiter=' ')
x2, y2 = data2[:, 0], data2[:, 1]

data3 = np.loadtxt('../TestsResults/Point9/Introsort.out', delimiter=' ')
x3, y3 = data3[:, 0], data3[:, 1]

data4 = np.loadtxt('../TestsResults/Point9/LSD.out', delimiter=' ')
x4, y4 = data4[:, 0], data4[:, 1]

data5 = np.loadtxt('../TestsResults/Point9/MergeIterative.out', delimiter=' ')
x5, y5 = data5[:, 0], data5[:, 1]

data6 = np.loadtxt('../TestsResults/Point9/QsortStd.out', delimiter=' ')
x6, y6 = data6[:, 0], data6[:, 1]

plt.figure()
plt.plot(x1, y1, 'b-', label='Heapsort')
plt.plot(x2, y2, 'r-', label='Hoare - mid element')
plt.plot(x3, y3, 'g-', label='Introsort')
plt.plot(x4, y4, 'm-', label='LSD')
plt.plot(x5, y5, 'y-', label='Merge iterative')
plt.plot(x6, y6, 'k-', label='Qsort std')

plt.xlabel('array size')
plt.ylabel('time')
plt.grid(True)
plt.legend()

plt.savefig('imgs/AllSortsO3.png')