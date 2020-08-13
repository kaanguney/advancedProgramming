# -*- coding: utf-8 -*-


################# exact algorithm #################

import random

def subsetsum(input, target):
    row, col = len(input) + 1, target + 1
    db = [[False] * col] * row
    for i in range(row):
        db[i][0] = True

    for i in range(1, row):
        for j in range(1, col):
            db[i][j] = db[i - 1][j]
            if db[i][j] == False and j >= input[i - 1]:
                db[i][j] = db[i - 1][j - input[i - 1]]

    return db[i][j]

################# exact algorithm #################





################# greedy algorithm #################

def mtgs(set, k):
    set.sort(reverse=True)
    for i in range(0, len(set)):
        #subset =[]
        k_ = k
        for j in range(i, len(set)):
            if set[j] <= k_:
                k_ = k_ - set[j]
        if k_ == 0:
            return 1
    return 0

################# greedy algorithm #################





################# testing accuracy #################

def main():
    
    correct = 0
    wrong = 0
    set = [0] * 150
    for acc in range(0, 750):   
        k = 45*1000

        for i in range(0, len(set)):
            set[i] = random.randint(1, 1000)
        set.sort(reverse=True)

        a = subsetsum(set, k)
        b = mtgs(set, k)
        if a == 1 and b == 1:
            correct = correct+1
        elif a ==1 and b == 0:
            wrong = wrong+1
        print("iteration", acc, "; accuracy:", correct/(correct+wrong))

main() # test call

################# testing accuracy #################







################# statistical testing #################

from time import process_time # for timing 
import statistics # for standard deviation

tval90 = 1.645 # fixed 
tval95 = 1.96 # fixed

import random

def mtgs(set, k):
    set.sort(reverse=True)
    for i in range(0, len(set)):
        subset =[]
        k_ = k
        for j in range(i, len(set)):
            if set[j] <= k_:
                k_ = k_ - set[j]
                subset.append(set[j])
        if k_ == 0:
            return 1
    return 0

alltimes = [] # storage for processing times

def stats(size,times):
  set=[0]*size
  k=(size/4)*float(10000)
  for x in range(1,times):
    for i in range(0,size):
      set[i]=random.randint(0,10000)
    starttime = process_time()
    mtgs(set,k)
    endtime = process_time()
    alltimes.append(endtime-starttime)

stats(25,100) # call for 25, 100 runs 

totaltime = sum(alltimes)
mean25 = totaltime/100
deviation25 = statistics.stdev(alltimes)
standarterror25 = deviation25 /10

upper95_25 = mean25+standarterror25 * tval95
lower95_25 = mean25-standarterror25 * tval95

upper90_25 = mean25+standarterror25 * tval90
lower90_25 = mean25-standarterror25 * tval90

alltimes = []

stats(50,100) # call for 50, 100 runs

totaltime = sum(alltimes)
mean50 = totaltime/100
deviation50 = statistics.stdev(alltimes)
standarterror50 = deviation50 /10

upper95_50 = mean50+standarterror50 * tval95
lower95_50 = mean50-standarterror50 * tval95

upper90_50 = mean50+standarterror25 * tval90
lower90_50 = mean50-standarterror25 * tval90

alltimes = []

stats(75,100) # call for 75, 100 runs 

totaltime = sum(alltimes)
mean75 = totaltime/100
deviation75 = statistics.stdev(alltimes)
standarterror75 = deviation75 /10
upper95_75 = mean75+standarterror75 * tval95
lower95_75 = mean75-standarterror75 * tval95

upper90_75 = mean75+standarterror75 * tval90
lower90_75 = mean75-standarterror75 * tval90

alltimes = []

stats(100,100) # call for 100, 100 runs

totaltime = sum(alltimes)
mean100 = totaltime/100
deviation100 = statistics.stdev(alltimes)
standarterror100 = deviation100 /10

upper95_100 = mean100+standarterror100 * tval95
lower95_100 = mean100-standarterror100 * tval95

upper90_100 = mean100+standarterror100 * tval90
lower90_100 = mean100-standarterror100 * tval90

alltimes = []

stats(150,100) # call for 150, 100 runs

totaltime = sum(alltimes)
mean150 = totaltime/100
deviation150 = statistics.stdev(alltimes)
standarterror150 = deviation150 /10

upper95_150 = mean150+standarterror150 * tval95
lower95_150 = mean150-standarterror150 * tval95


upper90_150 = mean150+standarterror150 * tval90
lower90_150 = mean150-standarterror150 * tval90

alltimes = []

# test with 250 runs

import math

stats(25,250) # call for 25, 250 runs 

totaltime = sum(alltimes)
mean25_250_runs = totaltime/250
deviation25_250_runs = statistics.stdev(alltimes)
standarterror25_250_runs = deviation25_250_runs / math.sqrt(250)

upper95_25_250_runs = mean25_250_runs+standarterror25_250_runs * tval95
lower95_25_250_runs = mean25_250_runs-standarterror25_250_runs * tval95

upper90_25_250_runs = mean25_250_runs+standarterror25_250_runs * tval90
lower90_25_250_runs = mean25_250_runs-standarterror25_250_runs * tval90


alltimes = []

stats(50,250) # call for 50, 250 runs

totaltime = sum(alltimes)
mean50_250_runs = totaltime/250
deviation50_250_runs = statistics.stdev(alltimes)
standarterror50_250_runs = deviation50_250_runs / math.sqrt(250)

upper95_50_250_runs = mean50_250_runs+standarterror50_250_runs * tval95
lower95_50_250_runs = mean50_250_runs-standarterror50_250_runs * tval95

upper90_50_250_runs = mean50_250_runs+standarterror50_250_runs * tval90
lower90_50_250_runs = mean50_250_runs-standarterror50_250_runs * tval90


alltimes = []

stats(75,250) # call for 75, 250 runs

totaltime = sum(alltimes)
mean75_250_runs = totaltime/250
deviation75_250_runs = statistics.stdev(alltimes)
standarterror75_250_runs = deviation75_250_runs / math.sqrt(250)

upper95_50_250_runs = mean75_250_runs+standarterror75_250_runs * tval95
lower95_75_250_runs = mean75_250_runs-standarterror75_250_runs * tval95


upper90_50_250_runs = mean75_250_runs+standarterror75_250_runs * tval90
lower90_75_250_runs = mean75_250_runs-standarterror75_250_runs * tval90

alltimes = []

stats(100,250) # call for 100, 250 runs

totaltime = sum(alltimes)
mean100_250_runs = totaltime/250
deviation100_250_runs = statistics.stdev(alltimes)
standarterror100_250_runs = deviation100_250_runs / math.sqrt(250)

upper95_100_250_runs = mean100_250_runs+standarterror100_250_runs * tval95
lower95_100_250_runs = mean100_250_runs-standarterror100_250_runs * tval95


upper90_100_250_runs = mean100_250_runs+standarterror100_250_runs * tval90
lower90_100_250_runs = mean100_250_runs-standarterror100_250_runs * tval90

alltimes = []

stats(150,250) # call for 150, 250 runs

totaltime = sum(alltimes)
mean150_250_runs = totaltime/250
deviation150_250_runs = statistics.stdev(alltimes)
standarterror150_250_runs = deviation150_250_runs / math.sqrt(250)

upper95_150_250_runs = mean150_250_runs+standarterror150_250_runs * tval95
lower95_150_250_runs = mean150_250_runs-standarterror150_250_runs * tval95

upper90_150_250_runs = mean150_250_runs+standarterror150_250_runs * tval90
lower90_150_250_runs = mean150_250_runs-standarterror150_250_runs * tval90


alltimes = []

# test with 500 runs

stats(25,500) # call for 25, 500 runs 

totaltime = sum(alltimes)
mean25_500_runs = totaltime/500
deviation25_500_runs = statistics.stdev(alltimes)
standarterror25_500_runs = deviation25_500_runs / math.sqrt(500)

upper95_25_500_runs = mean25_500_runs +standarterror25_500_runs * tval95
lower95_25_500_runs = mean25_500_runs -standarterror25_500_runs * tval95

upper90_25_500_runs = mean25_500_runs +standarterror25_500_runs * tval90
lower90_25_500_runs = mean25_500_runs -standarterror25_500_runs * tval90

alltimes = []

stats(50,500) # call for 50, 500 runs 

totaltime = sum(alltimes)
mean50_500_runs = totaltime/500
deviation50_500_runs = statistics.stdev(alltimes)
standarterror50_500_runs = deviation50_500_runs / math.sqrt(500)

upper95_50_500_runs = mean50_500_runs+standarterror50_500_runs * tval95
lower95_50_500_runs = mean50_500_runs-standarterror50_500_runs * tval95

upper90_50_500_runs = mean50_500_runs+standarterror50_500_runs * tval90
lower90_50_500_runs = mean50_500_runs-standarterror50_500_runs * tval90

alltimes = []

stats(75,500) # call for 75, 500 runs 

totaltime = sum(alltimes)
mean75_500_runs = totaltime/500
deviation_75_500_runs = statistics.stdev(alltimes)
standarterror75_500_runs = deviation75_500_runs / math.sqrt(500)

upper95_75_500_runs = mean75_500_runs+standarterror75_500_runs * tval95
lower95_75_500_runs = mean75_500_runs-standarterror75_500_runs * tval95

upper90_75_500_runs = mean75_500_runs+standarterror75_500_runs * tval90
lower90_75_500_runs = mean75_500_runs-standarterror75_500_runs * tval90

alltimes = []

stats(100,500) # call for 100, 500 runs 

totaltime = sum(alltimes)
mean100_500_runs = totaltime/500
deviation100_500_runs = statistics.stdev(alltimes)
standarterror100_500_runs = deviation100_500_runs / math.sqrt(500)

upper95_100_500_runs = mean100_500_runs+standarterror100_500_runs * tval95
lower95_100_500_runs = mean100_500_runs-standarterror100_500_runs * tval95

upper90_100_500_runs = mean100_500_runs+standarterror100_500_runs * tval90
lower90_100_500_runs = mean100_500_runs-standarterror100_500_runs * tval90

alltimes = []

stats(150,500) # call for 150, 500 runs 

totaltime = sum(alltimes)
mean150_500_runs = totaltime/500
deviation150_500_runs = statistics.stdev(alltimes)
standarterror150_500_runs = deviation150_500_runs / math.sqrt(500)

upper95_150_500_runs = mean150_500_runs+standarterror150_500_runs * tval95
lower95_150_500_runs = mean150_500_runs-standarterror150_500_runs * tval95


upper90_150_500_runs = mean150_500_runs+standarterror150_500_runs * tval90
lower90_150_500_runs = mean150_500_runs-standarterror150_500_runs * tval90

alltimes = []

# test with 1000 runs

stats(25,1000) # call for 25,1000 runs

totaltime = sum(alltimes)
mean25_1000_runs = totaltime/1000
deviation25_1000_runs = statistics.stdev(alltimes)
standarterror25_1000_runs = deviation25_1000_runs / math.sqrt(1000)

upper95_25_1000_runs = mean25_1000_runs+standarterror25_1000_runs * tval95
lower95_25_1000_runs = mean25_1000_runs-standarterror25_1000_runs * tval95

lower90_25_1000_runs = mean25_1000_runs+standarterror25_1000_runs * tval90
lower90_25_1000_runs = mean25_1000_runs-standarterror25_1000_runs * tval90

alltimes = []

stats(50,1000) # call for 50,1000 runs 

totaltime = sum(alltimes)
mean50_1000_runs = totaltime/1000
deviation50_1000_runs = statistics.stdev(alltimes)
standarterror50_1000_runs = deviation50_1000_runs / math.sqrt(1000)

upper95_50_1000_runs = mean50_1000_runs+standarterror50_1000_runs * tval95
lower95_50_1000_runs = mean50_1000_runs-standarterror50_1000_runs * tval95

upper90_50_1000_runs = mean50_1000_runs+standarterror50_1000_runs * tval90
lower90_50_1000_runs = mean50_1000_runs-standarterror50_1000_runs * tval90

alltimes = []

stats(75,1000) # call for 75,1000 runs 

totaltime = sum(alltimes)
mean75_1000_runs = totaltime/1000
deviation75_1000_runs = statistics.stdev(alltimes)
standarterror75_1000_runs = deviation75_1000_runs / math.sqrt(1000)

upper95_75_1000_runs = mean75_1000_runs+standarterror75_1000_runs * tval95
lower95_75_1000_runs = mean75_1000_runs-standarterror75_1000_runs * tval95


upper90_75_1000_runs = mean75_1000_runs+standarterror75_1000_runs * tval90
lower90_75_1000_runs = mean75_1000_runs-standarterror75_1000_runs * tval90

alltimes = []

stats(100,1000) # call for 100,1000 runs 

totaltime = sum(alltimes)
mean100_1000_runs = totaltime/1000
deviation100_1000_runs = statistics.stdev(alltimes)
standarterror100_1000_runs = deviation100_1000_runs / math.sqrt(1000)

upper95_100_1000_runs = mean100_1000_runs+standarterror100_1000_runs * tval95
lower95_100_1000_runs = mean100_1000_runs-standarterror100_1000_runs * tval95


upper90_100_1000_runs = mean100_1000_runs+standarterror100_1000_runs * tval90
lower90_100_1000_runs = mean100_1000_runs-standarterror100_1000_runs * tval90

alltimes = []

stats(150,1000) # call for 150,1000 runs 

totaltime = sum(alltimes)
mean150_1000_runs = totaltime/1000
deviation150_1000_runs = statistics.stdev(alltimes)
standarterror150_1000_runs = deviation150_1000_runs / math.sqrt(1000)

upper95_150_1000_runs = mean150_1000_runs+standarterror150_1000_runs * tval95
lower95_150_1000_runs = mean150_1000_runs-standarterror150_1000_runs * tval95


upper90_150_1000_runs = mean150_1000_runs+standarterror150_1000_runs * tval90
lower90_150_1000_runs = mean150_1000_runs-standarterror150_1000_runs * tval90

alltimes = []

mean150_1000_runs

mean100_1000_runs

################# statistical testing #################






################# example plotting, same method used for every graph #################

import matplotlib.pyplot as plt

fig,ax = plt.subplots(1,figsize=(12,8))
fig.suptitle("Mean Times(s) / Set Sizes", fontweight="bold")
plt.plot([25,50,75,100,150],[0.000071534,0.000221824,0.000351722,0.000501641,0.000698479],"tab:cyan")
plt.xlabel("Set Sizes", fontweight="bold")
plt.ylabel("Mean Times(s)", fontweight="bold")

################# example plotting, same method used for every graph #################
