import numpy as np
import matplotlib.pyplot as plt

plt.figure()

# Выбор отличающихся цветов для первых 7 графиков
colors = ['tab:blue', 'tab:orange', 'tab:green', 'tab:red', 'tab:purple', 'tab:brown', 'tab:pink']

for k in range(2, 16):
    data = np.loadtxt(f'../TestsResults/Point2/HeapSort_{k}', delimiter=' ')
    x, y = data[:, 0], data[:, 1]
    
    if k <= 8:
        color = colors[k-2]  # Используем выбранные цвета для первых 7 графиков
    else:
        color = plt.cm.viridis((k-2) / 13)  # Для остальных графиков используем цвет из colormap (здесь - виридис)
    
    plt.plot(x, y, color=color, label=f'rank {k}')

plt.xlabel('array size')
plt.ylabel('time')
plt.grid(True)
plt.legend()

plt.savefig('imgs/HeapSorts.png')
plt.show()