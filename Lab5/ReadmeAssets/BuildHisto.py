import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('TestsResults/StrHash/CRC32.out')

values_col1 = data[:, 0]
heights_col2 = data[:, 1]

plt.bar(values_col1, heights_col2, color='skyblue', edgecolor='black')
plt.xlabel('cell id')
plt.ylabel('collisions')
plt.title('histogram')
plt.grid(True)

plt.savefig('ReadmeAssets/imgs/CRC32.png')