export PATH=/software/gcc/9.3.0/bin:$PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib64:$LD_LIBRARY_PATH

#rm a.out
gcc main.c -g  -O2 -Wall
#echo "======= input1 ========================"
#./a.out < input1
#echo "======= input2 ========================"
#./a.out < input2
#echo "======= input3 ========================"
#./a.out < input3
echo "======= input4 ========================"
./a.out < input4
echo "======= input5 ========================"
./a.out < input5
echo "======= input6 ========================"
./a.out < input6
echo "======= input7 ========================"
./a.out < input7
echo "======= input8 ========================"
./a.out < input8
echo "======= input9 ========================"
./a.out < input9
