export PATH=/software/gcc/9.3.0/bin:$PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib64:$LD_LIBRARY_PATH

gcc main.c

./a.out < input
