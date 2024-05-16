import numpy as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('TestsResults/SPLAY/Inserts.out', delimiter=' ')
x1, y1 = data1[:, 0], data1[:, 1]
#data2 = np.loadtxt('TestsResults/Treap/Deletes.out', delimiter=' ')
#x2, y2 = data2[:, 0], data2[:, 1]
#data3 = np.loadtxt('TestsResults/AVL/Deletes.out', delimiter=' ')
#x3, y3 = data3[:, 0], data3[:, 1]

plt.figure()

plt.plot(x1, y1, 'b-', label='Tree')
#plt.plot(x2, y2, 'g-', label='Treap')
#plt.plot(x3, y3, 'm-', label='AVL')

plt.xlabel('number of operations')
plt.ylabel('time')
plt.grid(True)
plt.legend()

plt.savefig('ReadmeAssets/imgs/SPLAY_Inserts.png')