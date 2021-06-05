export PATH=/software/gcc/9.3.0/bin:$PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib64:$LD_LIBRARY_PATH


if [ -f "a1.out" ]; then
    rm a1.out
fi

gcc main3.c -g -Wall -o a1.out

if [ ! -f "a1.out" ]; then
    echo "a1.out does not exist!"
    exit
fi


#./a1.out < input1
#echo "============================="
#./a1.out < input2
#echo "============================="
#./a1.out < input3
