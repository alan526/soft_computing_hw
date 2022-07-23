from matplotlib import projections
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D
import imageio.v2
import math

p_size = 30
iter_num = 50

def drawscatter(path, target):
    color_value = np.zeros((p_size), int)

    for i in range(iter_num):
        df = pd.read_csv(path + str(i) + ".csv")
        position = np.array(df[0:p_size])
        position = position.astype(float)
        # draw 3D scatter
        fig = plt.figure(figsize=(8, 9))
        ax = Axes3D(fig, auto_add_to_figure=False)
        color_value[:] = i
        ax.set_position([0, 0, 0.8, 1.0])
        map = ax.scatter(position[:, 0], position[:, 1], position[:, 2], c=color_value, cmap='Spectral', vmin=0, vmax=iter_num)
        ax.set_xlim(-32, 32)
        ax.set_ylim(-32, 32)
        ax.set_zlim(-32, 32)
        ax.set_xlabel('X1')
        ax.set_ylabel('X2')
        ax.set_zlabel('X3')
        ax.set_title("Iter " + str(i), fontsize = 50)
        fig.add_axes(ax)
        cax = ax.inset_axes([1.08, 0.05, 0.05, 0.8], transform=ax.transAxes)
        fig.colorbar(map, ax=ax, cax=cax)

        plt.savefig(target + str(i) + ".png")
        plt.close(fig)
    print("scatter Down")

def draw_gbest_line(path, picname):
    g_fitness = []
    g_x = []
    sol_x = []
    gbest_sum = 0
    std_temp = 0
    fig = plt.figure(figsize=(16, 9))
    fig.add_subplot(121)
    for i in range(iter_num):
        df = pd.read_csv(path + str(i) + ".csv")
        temp = np.array(df[p_size+1:])
        temp = temp.astype(float)
        g_fitness.append(temp[0][3])
        gbest_sum = gbest_sum + temp[0][3]
        sol_x.append(temp[0][:])
        g_x.append(i+1)
    plt.plot(g_x, g_fitness, 'ro-', label='o')
    plt.legend(labels = ["fitness value"])
    plt.xlabel('Iteration')
    plt.ylabel('Fitness value')
    plt.title(picname)

    ax = fig.add_subplot(122)
    # calculate mean and std
    mean = gbest_sum / iter_num
    for i in range(iter_num):
        std_temp = std_temp + math.pow((g_fitness[i] - mean), 2)
    std = math.sqrt((std_temp / iter_num))
    plt.title("mean = " + str(mean) + "\nstd = " + str(std))
    # draw the iter table
    col_name = ["X1", "X2", "X3", "fitness_value"]
    ax.axis("tight")
    ax.axis("off")
    table = ax.table(cellText=sol_x, colLabels = col_name, loc = "center", rowLabels = g_x, cellLoc = "center")
    table.auto_set_font_size(False)
    table.set_fontsize(8)
    table.scale(1.2, 0.8)
    plt.savefig(picname + ".png")
    plt.close(fig)
    print("linechart Down")

def imgtogif(path, gifname):
    images = []
    for i in range(iter_num):
        images.append(imageio.v2.imread(path + str(i) + ".png"))
    imageio.v2.mimsave(gifname + ".gif", images)
    print("gif Down")

if __name__=='__main__':
    # GA plot
    drawscatter("./GA_record/iter", "./GA_record_fig/iter")
    draw_gbest_line("./GA_record/iter", "GA_gbest_linechart")
    imgtogif("./GA_record_fig/iter", "GA")
    # PSO plot
    drawscatter("./PSO_record/iter", "./PSO_record_fig/iter")
    draw_gbest_line("./PSO_record/iter", "PSO_gbest_linechart")
    imgtogif("./PSO_record_fig/iter", "PSO")
    print("plot finish")
