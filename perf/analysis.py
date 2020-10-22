#
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd 
import sys 

func1 = "multimod_p1"
func2 = "multimod_p2"
func3 = "multimod_p3"
rounds = 10

### 分析a, b, m的大小对运行时间的影响
'''
data1 = pd.read_csv(r"/home/james/ics-workbench/perf/RUNTIME_of_p1_task1", sep = '\s+', header = None)
data2 = pd.read_csv(r"/home/james/ics-workbench/perf/RUNTIME_of_p2_task1", sep = '\s+', header = None)
data3 = pd.read_csv(r"/home/james/ics-workbench/perf/RUNTIME_of_p3_task1", sep = '\s+', header = None)

data1[rounds] = data1.mean(axis = 1)
data2[rounds] = data2.mean(axis = 1)
data3[rounds] = data3.mean(axis = 1)

x = [2, 4, 8, 16, 32, 63]
y1 = list(data1[rounds])
y2 = list(data2[rounds])
y3 = list(data3[rounds])
plt.title("Runtime of size of input numbers")
plt.xlabel("hi of 1")
plt.ylabel("time(s)")
plt.plot(x, y1, label = func1, linewidth = 3, color = 'red', marker = 'o')
plt.plot(x, y2, label = func2, linewidth = 3, color = 'yellow', marker = 'o')
plt.plot(x, y3, label = func3, linewidth = 3, color = 'blue', marker = 'o')
plt.legend()
plt.show()'''

data1 = pd.read_csv(r"/home/james/ics-workbench/perf/RUNTIME_of_p1", sep = '\s+', header = None)
data2 = pd.read_csv(r"/home/james/ics-workbench/perf/RUNTIME_of_p2", sep = '\s+', header = None)
data3 = pd.read_csv(r"/home/james/ics-workbench/perf/RUNTIME_of_p3", sep = '\s+', header = None)

data1[rounds] = data1.mean(axis = 1)
data2[rounds] = data2.mean(axis = 1)
data3[rounds] = data3.mean(axis = 1)

x = [1, 2, 4, 8, 16, 32, 63]
y1 = list(data1[rounds])
y2 = list(data2[rounds])
y3 = list(data3[rounds])
plt.title("Runtime of # of 1 in input numbers")
plt.xlabel("num of 1")
plt.ylabel("time(s)")
plt.plot(x, y1, label = func1, linewidth = 2, color = 'red', marker = 'o')
plt.plot(x, y2, label = func2, linewidth = 2, color = 'yellow', marker = 'o')
plt.plot(x, y3, label = func3, linewidth = 2, color = 'blue', marker = 'o')
plt.legend()
plt.show()