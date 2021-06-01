import argparse
import random
import string as st

parser = argparse.ArgumentParser( description='Plot slices for sr-hydro' )
parser.add_argument( '-s',  action='store', required=True, type=int, dest='LenStr',  help='LenStr' )
parser.add_argument( '-p',  action='store', required=True, type=int, dest='LenPat',  help='LenPat' )

args=parser.parse_args()


LenStr = args.LenStr 
LenPat = args.LenPat 

string=""
pattern=""


for i in range(LenStr):
  string += random.choice(st.ascii_letters)


for j in range(LenPat):
  pattern += random.choice(st.ascii_letters)

print("1")
print(string)
print(pattern)
