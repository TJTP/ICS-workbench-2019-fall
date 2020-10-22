import numpy as np
import matplotlib.pyplot as plt
import pandas as pd 
import sys 


data1 = pd.read_csv(r"/home/james/ics-workbench/cachesim/ratio_tot_sz.txt", sep = '\s+', header = None)

y1 = list(data1[0])
x1 = list(data1[1])

plt.title("Relation between Hit Ratio and Cache Size")
plt.xlabel("total size width")
plt.ylabel("hit ratio")
plt.xticks(x1)
plt.ylim((0.995, 1.0))
plt.scatter(x1, y1, s = 20, c = 'r')
plt.show()

data2 = pd.read_csv(r"/home/james/ics-workbench/cachesim/ratio_asso_width.txt", sep = '\s+', header = None)

y2 = list(data2.loc[:7,0])
x2 = list(data2.loc[:7,1])

plt.title("Relation between Hit Ratio and Asso Width")
plt.xlabel("asso width")
plt.ylabel("hit ratio")
plt.xticks(x2)
plt.ylim((0.997, 1.0))
plt.scatter(x2, y2, s = 20, c = 'r')
plt.show()

y3 = list(data2.loc[8:10,0])
x3 = list(data2.loc[8:10,1])

plt.title("Relation between Hit Ratio and Asso Width")
plt.xlabel("asso width")
plt.ylabel("hit ratio")
plt.xticks(x3)
plt.ylim((0.5, 0.8))
plt.scatter(x3, y3, s = 20, c = 'r')
plt.show()

y4 = list(data2.loc[11:15,0])
x4 = list(data2.loc[11:15,1])

plt.title("Relation between Hit Ratio and Asso Width")
plt.xlabel("asso width")
plt.ylabel("hit ratio")
plt.xticks(x4)
plt.ylim((0.8, 1.0))
plt.scatter(x4, y4, s = 20, c = 'r')
plt.show()


data3 = pd.read_csv(r"/home/james/ics-workbench/cachesim/time_tot_width.txt", sep = '\s+', header = None)

y51 = list(data3.loc[0:6, 0])
y52 = list(data3.loc[7:13, 0])
y53 = list(data3.loc[14:20, 0])
y54 = list(data3.loc[21:27, 0])
x5 = list(data3.loc[:6, 1])

plt.title("Relation between Cache Cycle and Cache Size and Asso Width")
plt.xlabel("total size width")
plt.ylabel("cache cycle")
plt.xticks(x5)
plt.scatter(x5, y51, label = "asso width "+str(int(data3.iat[0,2])), s = 20, c = 'r')
plt.scatter(x5, y52, label = "asso width "+str(int(data3.iat[7,2])), s = 20, c = 'g')
plt.scatter(x5, y53, label = "asso width "+str(int(data3.iat[14,2])), s = 20, c = 'b')
plt.scatter(x5, y54, label = "asso width "+str(int(data3.iat[21,2])), s = 20, c = 'y')
plt.legend()
plt.show()