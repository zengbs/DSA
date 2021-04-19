export PATH=/software/gcc/9.3.0/bin:$PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/software/gcc/9.3.0/lib64:$LD_LIBRARY_PATH

gcc main1.c -o a1.out
gcc main3.c -o a2.out

printf "%d/%d\n"     `./a1.out < input0_1`          `./a2.out < input0_1`
printf "%d/%d\n"     `./a1.out < input1_3`          `./a2.out < input1_3`
printf "%d/%d\n"     `./a1.out < input2_2`          `./a2.out < input2_2`
printf "%d/%d\n"     `./a1.out < input3_4`          `./a2.out < input3_4`
printf "%d/%d\n"     `./a1.out < input4_1000`       `./a2.out < input4_1000`
printf "%d/%d\n"     `./a1.out < input5_5`          `./a2.out < input5_5`
printf "%d/%d\n"     `./a1.out < input6_1000`       `./a2.out < input6_1000`
printf "%d/%d\n"     `./a1.out < input7`            `./a2.out < input7`
printf "%d/%d\n"     `./a1.out < input8`            `./a2.out < input8`
