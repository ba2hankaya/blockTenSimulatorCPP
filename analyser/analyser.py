import sys
import matplotlib.pyplot as plt
import numpy as np
import argparse

parser = argparse.ArgumentParser(
        prog = 'Analyser.py',
        description = 'analyses the output of the simulator')
parser.add_argument(
        'files',
        nargs='+',
        help = 'List of files to process')
parser.add_argument(
        '-c',
        type=float,
        default=0.161,
        help = "bet return coefficient(default : 0.161)"
        )
args = parser.parse_args()

def calculateChances(filename):
    f = open(filename, "r")
    lines = []
    for line in f:
        line = line.strip()
        lines.append(line)
    scores=[]
    numOfAttempts=[]
    totalAttempt=0
    for index in range(1,len(lines)-1):
        scores.append(int(lines[index].split(' ')[0]))
        numOfAttempts.append(int(lines[index].split(' ')[2]))
        totalAttempt += numOfAttempts[index-1];
    total = 0;
    sumof = 0
    for i in range(len(numOfAttempts)):
        x = (numOfAttempts[i] / totalAttempt * 100)
        print(scores[i] , " : %" , x)
        total+= i * x
        sumof += args.c * i * x
    print("------------------------")
    print(filename)
    print("xfac" , total)
    print("return" , sumof)
    print("------------------------")
    return sumof
    f.close()
total = 0
count = 0
for arg in args.files:
    x = calculateChances(arg)
    total+=x
    count+=1
avg = total/count
print(avg)
