import argparse


parser = argparse.ArgumentParser( )
parser.add_argument( '-a',  action='store', required=True, type=int, dest='a',  help='a' )
parser.add_argument( '-b',  action='store', required=True, type=int, dest='b',  help='b' )
parser.add_argument( '-c',  action='store', required=True, type=int, dest='c',  help='c' )

args=parser.parse_args()

a  = args.a
b  = args.b
c  = args.c


aa =  7*a + 3* b -0*c
bb =  2*a + 1*b  -5*c
cc = -4*a -2*b + 11*c

print(aa)
print("%04d" % (bb))
print(cc)
