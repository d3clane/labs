import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('TestsResults/IntHash/Knuth.out')

values_col1 = data[:, 0]
heights_col2 = data[:, 1]

plt.bar(values_col1, heights_col2, color='skyblue', edgecolor='black')
plt.xlabel('list id')
plt.ylabel('list size')
plt.title('histogram')
plt.grid(True)

plt.ylim(top = 25)

plt.savefig('ReadmeAssets/imgs/Knuth.png')