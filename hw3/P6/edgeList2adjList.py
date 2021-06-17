import numpy as np


# Step0: Read numberVetexDouble from adj list in table
x = np.loadtxt("adjList", dtype=np.int8, usecols=0 )
numberVetexDouble = x[0]

# Step1: Read edge list from table
a = np.loadtxt("edgeList", dtype=np.int8, skiprows=1 )

# Step2: compute adj list
adjLst = [[] for _ in range(numberVetexDouble)]

a=a-1

for p in a:
  adjLst[p[0]].append(p[1]+1)
  adjLst[p[1]].append(p[0]+1)

# Step3: output adj list
File = open("adjList2", 'w')
print(numberVetexDouble, file=File)
for lst in adjLst:
  print(len(lst), *lst, sep=' ', file=File)
