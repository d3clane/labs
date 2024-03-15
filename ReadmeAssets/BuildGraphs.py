import numpy as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('../TestsResults/Point4/Hoare_big_tests.out', delimiter=' ')
x1, y1 = data1[:, 0], data1[:, 1]

data2 = np.loadtxt('../TestsResults/Point4/OneBranch_big_tests.out', delimiter=' ')
x2, y2 = data2[:, 0], data2[:, 1]

#data3 = np.loadtxt('../TestsResults/Point4/Ternary_duplicates_tests.out', delimiter=' ')
#x3, y3 = data3[:, 0], data3[:, 1]

#data4 = np.loadtxt('../TestsResults/Point1/Shell.out', delimiter=' ')
#x4, y4 = data4[:, 0], data4[:, 1]

plt.figure()
plt.plot(x1, y1, 'b-', label='Hoare')
plt.plot(x2, y2, 'r-', label='One branch hoare')
#plt.plot(x3, y3, 'g-', label='Ternary')
#plt.plot(x4, y4, 'm-', label='Shell sort')

plt.xlabel('array size')
plt.ylabel('time')
plt.grid(True)
plt.legend()

plt.savefig('imgs/QuickSortOptimization.png')