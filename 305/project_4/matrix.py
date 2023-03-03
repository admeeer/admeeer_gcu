import numpy as np
from scipy.integrate import odeint
import matplotlib.pyplot as plt
import math

row_1_plot = []
row_2_plot = []

def row_1(t):
    return 1-math.exp(t/20)

def row_2(t):
    return -1+math.exp(t/20)



# time sequence points, 0 to 100
t = np.linspace(0,100,101)

# get values
for i in range(101):
    row_1_plot.append(row_1(i))
    row_2_plot.append(row_2(i))



# plot results
plt.plot(t,row_1_plot, color="red", label='1-e^(t/20)')
plt.plot(t, row_2_plot, color="blue", label='-1+e^(t/20)')

# legend for labels
plt.legend()

# labels
plt.xlabel('t')
plt.ylabel('x(t)')
plt.show()
