export PATH=/software/gcc/9.3.0/bin:$PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib64:$LD_LIBRARY_PATH


if [ -f "a2.out" ]; then
    rm a2.out
fi

gcc main2.c -g -Wall -o a2.out

if [ ! -f "a2.out" ]; then
    echo "a2.out does not exist!"
    exit
fi


./a2.out < input1
echo "============================="
./a2.out < input2
echo "============================="
./a2.out < input3
