all: main validator/validator
	@./a.out < test_data

main: main.c api.h
	@gcc main_allen.c  -O3 -std=c11 -w

validator/validator: validator/validator.cpp
	@g++ validator/validator.cpp -o validator/validator -O3

clean:
	@rm a.out
