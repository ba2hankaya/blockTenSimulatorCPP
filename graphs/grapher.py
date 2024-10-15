import sys
import matplotlib.pyplot as plt
import numpy as np

def scaleData(data, _range):
    if _range == 0:
        return data;
    dmin = min(data)
    dmax = max(data)
    if dmax - dmin == range:
        return data;
    scaled = []
    for value in data:
        scaled.append(_range * (value - dmin) / (dmax-dmin))
    return scaled;


def plotFile(filename):
    _range = int(sys.argv[1])
    f = open(filename, "r")
    lines = []
    #readfile
    for line in f:
        line = line.strip()
        lines.append(line)
    scores=[]
    numOfAttempts=[]
    for index in range(1,len(lines)-1):
        scores.append(int(lines[index].split(' ')[0]))
        numOfAttempts.append(int(lines[index].split(' ')[2]))
    numOfAttempts = scaleData(numOfAttempts, _range)
    if mode == 1:
        if not labelbool:
            plt.plot(np.array(scores),np.array(numOfAttempts))
        else:
            plt.plot(np.array(scores),np.array(numOfAttempts),label=filename[:-4])
    elif mode == 2:
        if not labelbool:  
            plt.plot(np.array(scores),np.array(numOfAttempts))
        else:
            plt.plot(np.array(scores),np.array(numOfAttempts),label=filename[:-4])

mode = sys.argv[-1]
labelbool = sys.argv[-2]
for arg in sys.argv[2:-3]:
    plotFile(arg)
plt.locator_params(axis='y', nbins=20)
plt.xticks([*range(0,25)])
plt.grid()
plt.xlabel("Scores")
plt.ylabel("Num of Attempts")
if labelbool:
    plt.legend()
fig = plt.gcf()
fig.savefig(sys.argv[-1] + "_graph.png")

