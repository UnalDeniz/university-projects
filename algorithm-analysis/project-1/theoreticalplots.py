import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(1, 250)
theoreticalbest = [0 for i in range(5)]
theoreticalworst = [0 for i in range(5)]
theoreticalaverage = [0 for i in range(5)]

listsize = [1,5,10,25,50,75,100,150,200,250]
besttime = [54.836273193359375, 114.44091796875, 405.31158447265625, 2675.056457519531, 13482.57064819336, 32000.54168701172, 57203.76968383789, 144357.68127441406, 252788.06686401367, 394299.0303039551]
averagetime = [15.894571940104167, 271.00245157877605, 4089.673360188802, 72786.01328531901, 894629.955291748, 4200987.021128337, 12194737.593332927, 58452288.30973308, 189342065.6522115, 442177359.2631022]
worsttime = [23.84185791015625, 295.6390380859375, 3113.746643066406, 108175.27770996094, 1704573.631286621, 8648252.487182617, 27143588.066101074, 138607208.72879028, 431323366.1651611, 1054366879.4631958]
############################################
fig, ax = plt.subplots()
theoreticalbest[0] = x
ax.plot(x, theoreticalbest[0], label='theoric1')
############################################
theoreticalbest[1] = (np.log2(x+1)+1)*(x+1)*x/2
ax.plot(x, theoreticalbest[1], label='theoric2')
############################################
############################################
theoreticalbest[2] = 0 * x
ax.plot(x, theoreticalbest[2], label='theoric3')
############################################
############################################
theoreticalbest[3] = 0 * x
ax.plot(x, theoreticalbest[3], label='theoric4')
############################################
theoreticalbest[4] = 0 * x
ax.plot(x, theoreticalbest[4], label='theoric5')
############################################
ax.plot(listsize, besttime, label='real')
ax.set(xlabel='input size (N)', ylabel='complexity', title='best case of operation 5')
ax.legend()
fig.savefig("best.png")
############################################
fig, ax = plt.subplots()
theoreticalworst[0] = x
ax.plot(x, theoreticalworst[0], label='theoric1')
############################################
theoreticalworst[1] = x*x*(x+1)*(2*x+1)/6
ax.plot(x, theoreticalworst[1], label='theoric2')
############################################
theoreticalworst[2] = x*x*(x+1)*(2*x+1)/6
ax.plot(x, theoreticalworst[2], label='theoric3')
############################################
theoreticalworst[3] = x ** 3
ax.plot(x, theoreticalworst[3], label='theoric4')
############################################
theoreticalworst[4] = (x+1)*x/2
ax.plot(x, theoreticalworst[4], label='theoric5')
ax.plot(listsize, worsttime, label='real')
ax.set(xlabel='input size (N)', ylabel='complexity', title='worst case of operation 5')
ax.legend()
fig.savefig("worst.png")
############################################
fig, ax = plt.subplots()
theoreticalaverage[0] = x
ax.plot(x, theoreticalaverage[0], label='theoric')
############################################
theoreticalaverage[1] = x*(x+1)/6*(np.log2(x+1)+1)+x**3*(np.log2(x+1)+1)/3+x**2*(x+1)*(2*x+1)/18
ax.plot(x, theoreticalaverage[1], label='theoric')
############################################
theoreticalaverage[2] = x**3*(np.log2(x+1)+1)/3+x**2*(x+1)*(2*x+1)/18
ax.plot(x, theoreticalaverage[2], label='theoric')
############################################
theoreticalaverage[3] = (x ** 3 + x ** 2)/3
ax.plot(x, theoreticalaverage[3], label='theoric')
############################################
theoreticalaverage[4] = (x+1)*x/6
ax.plot(x, theoreticalaverage[4], label='theoric')
ax.plot(listsize, averagetime, label='real')
ax.set(xlabel='input size (N)', ylabel='complexity', title='average case of operation 5')
ax.legend()
fig.savefig("average.png")
