import numpy as np
from scipy.integrate import *
import matplotlib.pyplot as plt

import math


t = np.linspace(0, 100, 100)


def green_1(x):
    return ((math.pow(x, 2))/2) -((3*t)/2)+(3/4)-((3*(math.exp(-2*x)))/4)

def green_2(x):
    return -4 * math.cos(x) + 4

def homo_1(x):
    return (3/2)-((3/4)*math.exp(-2*x))

def homo_2(x):
    return -4 * math.cos(x)

g_1_plot = []
g_2_plot = []

h_1_plot = []
h_2_plot = []

for i in range(100):
    g_1_plot.append(green_1(i))
    g_2_plot.append(green_2(i))

    h_1_plot.append(homo_1(i))
    h_2_plot.append(homo_2(i))


plt.figure(1)
plt.title("Greens function first equation")
plt.plot(t, g_1_plot)

plt.figure(2)
plt.title("Greens function second equation")
plt.plot(t, g_2_plot)

plt.figure(3)
plt.title("Homogenous equation first equation")
plt.plot(t, h_1_plot)

plt.figure(4)
plt.title("Homogenous equation second equation")
plt.plot(t, h_2_plot)

#plt.figure(5)
fig, axs1 = plt.subplots(2)
plt.title("Greens vs. Homogenous function, first equation")
axs1[0].plot(t, g_1_plot)
axs1[1].plot(t, h_1_plot)

#plt.figure(6)
fig, axs2 = plt.subplots(2)
plt.title("Greens vs. Homogenous function, second equation")
axs2[0].plot(t, g_2_plot)
axs2[1].plot(t, h_2_plot)

plt.show()
