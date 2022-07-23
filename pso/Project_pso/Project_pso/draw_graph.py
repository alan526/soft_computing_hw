from matplotlib import projections
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D

fig = plt.figure()
ax = Axes3D(fig, auto_add_to_figure=False)
for i in range(50):
    df = pd.read_csv("./record/iter"+str(i)+".csv")
    position = np.array(df[0:10])
    position = position.astype(float)
    # 設定ax為散佈圖
    ax.scatter(position[:,0], position[:,1], position[:,2], c ='black')
    ax.set_xlim(-32, 32)
    ax.set_ylim(-32, 32)
    ax.set_zlim(-32, 32)
    ax.set_xlabel('X1')
    ax.set_ylabel('X2')
    ax.set_zlabel('X3')
    ax.set_title("Iteration_"+str(i))
    fig.add_axes(ax)
    plt.savefig("./record_fig/iter"+str(i)+".png")
    plt.clf()
    print(i)
    

