import numpy as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('../Output/Test4Arr.txt', delimiter=',')
x1, y1 = data1[:, 0], data1[:, 1]

data2 = np.loadtxt('../Output/Test4List.txt', delimiter=',')
x2, y2 = data2[:, 0], data2[:, 1]

plt.figure()
plt.plot(x1, y1, 'b-', label='Array')
plt.plot(x2, y2, 'r-', label='List')

plt.xlabel('n')
plt.ylabel('time')
plt.grid(True)
plt.legend()

plt.savefig('imgs/output.png')