export PATH=/software/gcc/9.3.0/bin:$PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib64:$LD_LIBRARY_PATH


if [ -f "a.out" ]; then
    rm a.out
fi

gcc main.c -g -Wall

if [ ! -f "a.out" ]; then
    echo "a.out does not exist!"
    exit
fi


./a.out < input1
echo "============================="
./a.out < input2
echo "============================="
./a.out < input3
