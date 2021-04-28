import numpy as np
import matplotlib.pyplot as plt
from cycler import cycler


x = np.linspace(-17,+14,num=1000)

# input 1
#P = [12,   7,-10,  12, 9]
#Q = [11,   5 , 5, -16, 5]
#R = [-2, -13, -8,  8, 10]

# input 2
P = [ 2,  -3,  6, -16, 0]
Q = [-7, -14, -5,   1, 6]
R = [-12,  5,  9,  13,-8]

# input 3
#P = [2,   14, -16,  -7, 13]
#Q = [7,   14,   0,   7, -5]
#R = [11, -12,   8, -12, -1]

#P = [1,2,3]
#Q = [2,3,4]
#R = [3,4,1]



P = np.array(P)
Q = np.array(Q)
R = np.array(R)


color = ['r', 'g', 'b', 'y', 'k']

for i in range(len(P)):
  if ( (P[i]-Q[i]) == 0 ):
    plt.vlines(Q[i],0,1, color=color[i])
    sploePR = 1.0 / (P[i]-R[i])

  if ( P[i]-R[i] != 0 ):
    sploePR = 1.0 / (P[i]-R[i])
    PR = 0 + sploePR*( x - R[i] )
    plt.plot(x, PR, color=color[i])

  if ( P[i]-R[i] != 0 and P[i]-Q[i] != 0 ):
    sploePQ = 1.0 / (P[i]-Q[i])
    sploePR = 1.0 / (P[i]-R[i])
    PQ = 0 + sploePQ*( x - Q[i] )
    PR = 0 + sploePR*( x - R[i] )
    plt.plot(x, PQ, color=color[i])
    plt.plot(x, PR, color=color[i])

  
plt.hlines(1,min(x),max(x))
plt.hlines(0,min(x),max(x))


plt.ylim(0,1)
plt.xlim(min(x),max(x))
plt.show()
