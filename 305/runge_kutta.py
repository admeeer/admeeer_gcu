import numpy as np
from scipy.integrate import *
import matplotlib.pyplot as plt

import math

xplot = []
yplot = []

x0 = 2
y0 = 1
h = 0.3
n = 5

xplot.append(x0)
yplot.append(y0)

print(f"x0 = {x0} and y0 = {y0}.")

#   recursive runge kutta function, iterates n times
def _solve_expression(x, y):
    #print(f"x is {x} and y is {y}")
    # this is where we input the expression
    return -y+math.log(x)

# o lets the function know how many times its iterated, it is the inverse of n
def runge_kutta(x, y, h, n, order=1):

    if n == 0:
     return
    else:
    
     k1 = _solve_expression(x, y)
     k2 = _solve_expression(x+(h/2),y+(h/2)*k1)
     k3 = _solve_expression(x+(h/2),y+(h/2)*k2)
     k4 = _solve_expression(x+h, y+h*k3)

     # for debugging purposes
     #print(f"k1 is {round(k1, 5)} and k2 is {round(k2, 5)} and k3 is {round(k3, 5)} and k4 is {round(k4, 5)}")

     t = (1/6)*(k1+(2*k2)+(2*k3)+k4)

     yn = y + h*t
     xn = x + h

     xplot.append(xn)
     yplot.append(yn)

     print(f"x{order} = {round(xn, 5)} and y{order} = {round(yn, 5)}.")

     runge_kutta(xn, yn, h, n-1, order+1)

# call runge kutta function with our x0, y0, h, and n parameters
runge_kutta(x0,y0,h,n)



# model must be in the form of (y, t) or else odeint wont use params
def model(y, t):
    return -y+math.log(t)
# create a list of our x values
t = np.linspace(x0, x0+(n*h), n+1)

rk_odeint_test = odeint(model, y0, t)

# print the x and y values of odeint
print(f"--------------------\n x is {t}\n y is {rk_odeint_test}\n")

# plot manual RungeKutta
plt.figure(1)
plt.plot(xplot, yplot)

# plot ode RK
plt.figure(2)
plt.plot(t, rk_odeint_test)

# subplots
fig, axs = plt.subplots(2)
fig.suptitle('Subplots')
axs[0].plot(xplot, yplot)
axs[1].plot(t, rk_odeint_test)
plt.show()