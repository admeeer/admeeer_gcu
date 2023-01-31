



#   recursive runge kutta function, iterates n times
def _solve_expression(x, y):
    # this is where we input the expression
    return -((3/x)+y)/(3*x*y)

# o lets the function know how many times its iterated, it is the inverse of n
def runge_kutta(x, y, h, n, o=1):

    if n == 0:
     return
    else:
    
     k1 = _solve_expression(x, y)
     k2 = _solve_expression(x+(h/2),y+(h/2)*k1)
     k3 = _solve_expression(x+(h/2),y+(h/2)*k2)
     k4 = _solve_expression(x+h, y+h*k3)

     # for debugging purposes
     # print(f"k1 is {round(k1, 5)} and k2 is {round(k2, 5)} and k3 is {round(k3, 5)} and k4 is {round(k4, 5)}")

     t4 = (1/6)*(k1+2*k2+2*k3+2*k4)

     yn = y + h*t4
     xn = x + h

     print(f"x{o} = {round(xn, 5)} and y{o} = {round(yn, 5)}.")

     runge_kutta(xn, yn, h, n-1, o+1)

# call runge kutta function with our x0, y0, h, and n parameters
runge_kutta(1,1,0.1,3)
