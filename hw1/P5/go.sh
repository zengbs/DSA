gcc -O2 main_${1}.c -std=c11
time ./a.out < input > log_${1}
