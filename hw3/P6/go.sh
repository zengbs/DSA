#export PATH=/software/gcc/9.3.0/bin:$PATH
#export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib:$LD_LIBRARY_PATH
#export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib64:$LD_LIBRARY_PATH



rm a.out
gcc main3.c -g -Wall  -o a.out



./a.out < input1
echo "============================="
./a.out < input2
echo "============================="
./a.out < input3
echo "============================="
./a.out < input4
