compile = gcc
flags = -Wall -Werror -Wextra --coverage
12 =-lcheck


all: tests 

tests: s21_memchr.o string_tests.o
	$(compile) $(flags) $(12) s21_memchr.o string_tests.o -o test

s21_memchr.o: s21_memchr.c
	$(compile) -c $(flags) s21_memchr.c -o s21_memchr.o

string_tests.o: string_tests.c
	$(compile) -c $(flags) string_tests.c -o string_tests.o

gcov_report:
	./test
	lcov --capture --directory . --output-file=coverage.info
	genhtml coverage.info --output-directory=result
	open ./result/index.html

clean:
	-rm -rf *.o *.gcda *.gcno *result
	