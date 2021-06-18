from random import randrange

import numpy as np


# Step1: generate edge list

numberVetexDouble = 100

# first create an array of all possible pair1 from (0,0) to (9,19)
pair1 = np.dstack(np.meshgrid(np.arange(numberVetexDouble), np.arange(numberVetexDouble))).reshape(-1,2)


pair1 = np.unique(np.sort(pair1, axis=1).view(','.join([pair1.dtype.char]*2))).view(pair1.dtype).reshape(-1, 2)

# random permutation
pair1 = np.random.permutation(pair1)


pair2 = []*numberVetexDouble

c = 0
for p in pair1:
  if p[0] != p[1] and c < numberVetexDouble:
    pair2.append(p)
    c=c+1

# Step2: compute adj list

File2 = open("adjList1", 'w')

print(numberVetexDouble, file=File2)

adjLst = [[] for _ in range(numberVetexDouble)]


for p in pair2:
  adjLst[p[0]].append(p[1]+1)
  adjLst[p[1]].append(p[0]+1)

# Step3: output adj list

for lst in adjLst:
  print(len(lst), *lst, sep=' ', file=File2)

# Step4: output edge list

File1 = open("edgeList1", 'w')
print("Yes", file=File1)
for p in pair2:
    print(p[0]+1, p[1]+1, file=File1)

File1.close()
