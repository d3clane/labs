import numpy as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('TestsResults/AVL/Deletes.out', delimiter=' ')
x1, y1 = data1[:, 0], data1[:, 1]

plt.figure()
plt.plot(x1, y1, 'b-', label='List')

plt.xlabel('number of operations')
plt.ylabel('time')
plt.grid(True)
plt.legend()

plt.savefig('ReadmeAssets/imgs/AVL_Deletes.png')