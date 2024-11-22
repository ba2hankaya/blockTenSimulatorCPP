import sys
import matplotlib.pyplot as plt
import numpy as np
import argparse

parser = argparse.ArgumentParser(
        prog='GraphDrawer',
        description='Draws graphs using datasets'
        )

parser.add_argument(
        'files',
        nargs='+',
        help='files or file to process'
        )
parser.add_argument(
        '-m',
        type=int,
        choices=[0,1],
        default=1,
        help="1 for scatter, 0 for line (def = 1))"
        )
parser.add_argument(
        '-o',
        help = "output file"
        )
parser.add_argument(
        '-l',
        action="store_true",
        help= "label the data(include -l to label, omit to not)"
        )
parser.add_argument(
        '-r',
        type=int,
        help='range of numattempts to scale the graph'
        )

args = parser.parse_args()

def scaleData(data, _range):
    if _range == 0:
        return data;
    dmin = min(data)
    dmax = max(data)
    if dmax - dmin == _range:
        return data;
    scaled = []
    for value in data:
        scaled.append(_range * (value - dmin) / (dmax-dmin))
    return scaled;


def plotFile(filename):
    _range = args.r
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
    x = np.array(scores)
    y = np.array(numOfAttempts)
    filename = filename.split('/')[-1]
    if args.m == True:
        plt.scatter(x,y,label=filename)
    else:
        plt.plot(x,y,label=filename)
    plt.title(args.o)

for filename in args.files:
    plotFile(filename)
plt.locator_params(axis='y', nbins=20)
plt.xticks([*range(0,25)])
plt.grid()
plt.xlabel("Scores")
plt.ylabel("Num of Attempts")
if args.l:
    plt.legend()
fig = plt.gcf()
fig.savefig(args.o)

