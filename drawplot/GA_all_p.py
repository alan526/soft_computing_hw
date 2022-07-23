import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D

p_size = 30
iter_num = 50

fig2 = plt.figure()
ax2 = Axes3D(fig2, auto_add_to_figure=False)
# color_map = plt.cm.get_cmap()
value = np.zeros((p_size*iter_num), int)

x1 = np.array([])
x2 = np.array([])
x3 = np.array([])
for i in range(iter_num):
    df = pd.read_csv("./GA_record/iter"+str(i)+".csv")
    position = np.array(df[0:p_size])
    position = position.astype(float)
    value[i*p_size:i*p_size+p_size] = i
    # print(value[i*p_size:i*p_size+p_size])
    tempx1 = np.array(position[:,0])
    tempx1 = tempx1.flatten()
    x1 = np.concatenate((x1, tempx1))
    tempx2 = np.array(position[:, 1])
    tempx2 = tempx2.flatten()
    x2 = np.concatenate((x2, tempx2))
    tempx3 = np.array(position[:, 2])
    tempx3 = tempx3.flatten()
    x3 = np.concatenate((x3, tempx3))
# print(value.shape)
# cmap='gist_rainbow''Spectral'
map = ax2.scatter(x1, x2, x3, c = value, cmap='Spectral')
ax2.set_xlim(-32, 32)
ax2.set_ylim(-32, 32)
ax2.set_zlim(-32, 32)
ax2.set_xlabel('X1')
ax2.set_ylabel('X2')
ax2.set_zlabel('X3')
fig2.add_axes(ax2)
fig2.colorbar(map, ax = ax2)
plt.show()