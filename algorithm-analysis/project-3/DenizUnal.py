import random 
import time
import sys

sys.setrecursionlimit(10**6)

def quick_sort(arr, alg_type, low, high):
    if high > low:
        if alg_type == 3:
            permute(arr)
            alg_type = 1
        pos = rearrange(arr, alg_type, low, high)
        quick_sort(arr, alg_type, low, pos-1)
        quick_sort(arr, alg_type, pos+1, high)


def permute(arr):
    for i in range(len(arr)-1):
        j = random.randint(i, len(arr)-1)
        temp = arr[i]
        arr[i] = arr[j]
        arr[j] = temp

def rearrange(arr, alg_type, low, high):
    right = low
    left = high

    if alg_type == 1:
        x_loc = low
        x = arr[low]
    elif alg_type == 2:
        x_loc = random.randint(low, high)
        x = arr[x_loc]
    else:
        three_elements = [arr[low], arr[high], arr[(high+low)//2]]
        x = sorted(three_elements)[1]
        for i in [low, high, (high+low)//2]:
            if arr[i] == x:
                x_loc = i

    while right < left:
        while right < left and arr[right] <= x:
            right += 1
        while arr[left] > x:
            left -= 1
        if right < left:
            if left == x_loc:
                x_loc = right
            temp = arr[right]
            arr[right] = arr[left]
            arr[left] = temp

    pos = left
    if x_loc > pos:
        pos = right
    arr[x_loc] = arr[pos]
    arr[pos] = x
    return pos

def inputme(typ, size):
    lst = [[],[],[],[],[],[]]
    if typ == 4:
        for x in lst:
            for i in range(size):
                x.append(1)
    elif typ == 1:
        for x in lst:
            for i in range(size):
                x.append(random.randint(1,size*10))
    elif typ == 2:
        for x in lst:
            for i in range(size):
                x.append(random.randint(1,0.75*size))
    elif typ == 3:
        for x in lst:
            for i in range(size):
                x.append(random.randint(1,0.25*size))

    wrst= lst.pop(5)
    wrst.sort()
    return ([lst,wrst])

sze = 10000
data100 = inputme(4, sze)

for i in range(5):
    for j in range(sze):
        print(data100[0][i][j], end="-")
    print("---------")

for i in range(sze):
    print(data100[1][i], end="-")

print("--------")

for i in range(1,5):
    enter = time.time()
    for j in range(5):
        quick_sort(data100[0][j], i, 0, sze-1)

    exitt = time.time()
    print("ver", i, "avg", (exitt-enter)/5)

    enter = time.time()
    quick_sort(data100[1], i, 0, sze-1)

    exitt = time.time()
    print("ver", i, "worst", exitt-enter)

