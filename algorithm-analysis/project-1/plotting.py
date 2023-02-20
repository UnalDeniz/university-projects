import math 
import random
import time
import matplotlib.pyplot as plt
import numpy as np


def Example(arr):
    n = len(arr)
    arr2 = [0,0,0,0,0]

    for i in range(n):
        if(arr[i] == 0):
            for t1 in range(i,n):
                p1 = t1**(1/2)
                x1 = n+1
                while(x1 >= 1):
                    x1 = math.floor(x1 / 2)
                    arr2[i % 5] = arr2[i % 5] + 1
        elif(arr[i] == 1):
            for t2 in range(n,0,-1):
                for p2 in range(1,n+1):
                    x2 = n+1
                    while(x2 > 0):
                        x2 = math.floor(x2/2)
                        arr2[i%5] = arr2[i%5] + 1
        elif(arr[i] == 2):
            for t3 in range(1,n+1):
                x3 = t3+1
                for p3 in range(t3**2):
                    arr2[i%5] = arr2[i%5] + 1

    return arr2

listsize = [1,5,10,25,50,75,100,150,200,250]
#listsize = np.linspace(1, 250)
listbestworst = [[[0 for k in range(i)] if j % 2 == 0 else [2 for k in range(i)] for j in range(2)] for i in listsize]
listavg = [[[random.randint(0,2) for k in range(i)] for j in range(3)] for i in listsize]

besttime = [0 for i in range(10)]
worsttime = [0 for i in range(10)]
averagetime = [0 for i in range(10)]

for i in range(10):
    start = time.time()
    Example(listbestworst[i][0])
    end = time.time()
    besttime[i] = end - start
    print("Case: best Size:", len(listbestworst[i][0]), "Elapsed Time:", end-start)

    start = time.time()
    Example(listbestworst[i][1])
    end = time.time()
    worsttime[i] = end - start
    print("Case: worst Size:", len(listbestworst[i][0]), "Elapsed Time:", end-start)

    avg = 0
    for j in range(3):
        start = time.time()
        Example(listavg[i][j])
        end = time.time()
        avg += end - start
	
    avg = avg/3
    averagetime[i] = avg
    print("Case average Size:", len(listavg[i][0]), "Elapsed Time:", avg)


fig, ax = plt.subplots()
ax.plot(listsize, besttime)
ax.set(xlabel='input size (N)', ylabel='time (seconds)', title='best case')
fig.savefig("best.png")
############################################
fig, ax = plt.subplots()
ax.plot(listsize, worsttime)
ax.set(xlabel='input size (N)', ylabel='time (seconds)', title='worst case')
fig.savefig("worst.png")
############################################
fig, ax = plt.subplots()
ax.plot(listsize, averagetime)
ax.set(xlabel='input size (N)', ylabel='time (seconds)', title='average case')
fig.savefig("average.png")