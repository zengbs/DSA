export PATH=/software/gcc/9.3.0/bin:$PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib64:$LD_LIBRARY_PATH

rm a.out
gcc main.c -g  -O2 -Wall
#./a.out < input1
#./a.out < input2
#./a.out < input3
./a.out < input4
