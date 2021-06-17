from random import randrange

import numpy as np




File1 = open("listEdge", 'w')
print("Yes", file=File1)
for p in pair2:
    print(p[0]+1, p[1]+1, file=File1)

File1.close()
