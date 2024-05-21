import numpy as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('TestsResults/Ops/Ops2List.out', delimiter=' ')
x1, y1 = data1[:, 0], data1[:, 1]

data2 = np.loadtxt('TestsResults/Ops/Ops2Linear.out', delimiter=' ')
x2, y2 = data2[:, 0], data2[:, 1]

data3 = np.loadtxt('TestsResults/Ops/Ops2Quadratic.out', delimiter=' ')
x3, y3 = data3[:, 0], data3[:, 1]

data4 = np.loadtxt('TestsResults/Ops/Ops2Hash.out', delimiter=' ')
x4, y4 = data4[:, 0], data4[:, 1]

plt.figure()
plt.plot(x1, y1, 'b-', label='List')
plt.plot(x2, y2, 'r-', label='Open linear')
plt.plot(x3, y3, 'g-', label='Open quadratic')
plt.plot(x4, y4, 'm-', label='Open hash')

plt.xlabel('number of operations')
plt.ylabel('time')
plt.grid(True)
plt.legend()

plt.savefig('ReadmeAssets/imgs/Ops2.png')