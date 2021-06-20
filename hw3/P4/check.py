import fileinput


c=0

for line in fileinput.input():
   if c==0:
     T       = line.rstrip()
   if c==1:
     String0  = line.rstrip()
   if c==2:
     Pattern0 = line.rstrip()
   c=c+1

String  = list(String0)
Pattern = list(Pattern0)


c=0
time=0

garble_length = []


for i in range(len(String)):


  if String[i] in Pattern:
    c=c+1
    if time is 0:
      tail = i
    time=time+1
    Pattern[Pattern.index(String[i])] = ""


  if c is len(Pattern):
    head = i
    garble_length.append(head-tail+1)

    c = 0
    time=0
    Pattern = list(Pattern0)

     
  
    if {i:garble_length.count(i) for i in garble_length}[head-tail+1] is 1:
      for j in range(tail, i+1):
         String = list(String)
         String[j] = ""


String = ''.join(map(str, String))
Pattern = ''.join(map(str, Pattern))

print(String)
