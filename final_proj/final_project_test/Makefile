main: main.c api.h
	gcc main.c  -O3 -std=c11 -w

validator/validator: validator/validator.cpp
	g++ validator/validator.cpp -o validator/validator -O3

.PHONY=all
all: main validator/validator
	./a.out < testdata/test.in | validator/validator
