import numpy as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('TestsResults/LoadFactor/LoadFactor.out', delimiter=' ')
x1, y1 = data1[:, 0], data1[:, 1]

plt.figure()
plt.plot(x1, y1, 'b-', label='Load factor')

plt.xlabel('load factor')
plt.ylabel('time')
plt.grid(True)
plt.legend()

plt.savefig('ReadmeAssets/imgs/LoadFactor.png')