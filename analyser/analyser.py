import sys
import matplotlib.pyplot as plt
import numpy as np



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
        sumof += 0.165 * i * x
    print("------------------------")
    print(filename)
    print("xfac" , total)
    print("return" , sumof)
    print("------------------------")
    return sumof
    f.close()
total = 0
count = 0
for arg in sys.argv[1:]:
    x = calculateChances(arg)
    total+=x
    count+=1
avg = total/count
print(avg)
