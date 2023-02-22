import numpy as np
from scipy.integrate import odeint
import matplotlib.pyplot as plt

#A simple example of an ODE model for data degradation on an HDD could be

# function returns dD/dt
def data_deg(data, t):
    # temperature
    temperature = 37.77
    # humidity
    humidity = 0.5
    # strength of magnetic field
    b = 0.5
    # constant, rate of degradation caused by changes in temperature and humidity
    k1 = 0.01
    # constant, rate of degradation caused by changes in magnetic field
    k2 = 0.005

    dDdt = -k1 * temperature * humidity * data - k2 * b * data
    return dDdt

# initial condition, data, in GB
d0 = [100, 500, 999, 1899]

# time sequence points, in years
t = np.linspace(0,10)

# solve ODE
r = odeint(data_deg,d0,t)

# plot results
plt.plot(t,r[:,0], color="purple", label='d0 = 100')
plt.plot(t, r[:,1], color="yellow", label='d0 = 500')
plt.plot(t, r[:,2], color="blue", label='d0 = 999')
plt.plot(t, r[:,3], color="black", label='d0 = 1899')

# legend for labels
plt.legend()

# labels
plt.xlabel('time in years')
plt.ylabel('data_deg(t)')
plt.show()
