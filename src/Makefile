compile = gcc
flags = -Wall -Werror -Wextra
12 =-lcheck
coverFlag =--coverage


all: tests 

tests: s21_memchr.o s21_memcpy.o s21_memcmp.o string_tests.o s21_memmove.o
	$(compile) $(flags) $(12) $(coverFlag) s21_memchr.o s21_memcpy.o s21_memcmp.o s21_memmove.o string_tests.o -o test

s21_memchr.o: s21_memchr.c
	$(compile) -c $(flags) $(coverFlag) s21_memchr.c -o s21_memchr.o

s21_memcpy.o: s21_memcpy.c
	$(compile) -c $(flags) $(coverFlag) s21_memcpy.c -o s21_memcpy.o

s21_memcmp.o: s21_memcmp.c
	$(compile) -c $(flags) $(coverFlag) s21_memcmp.c -o s21_memcmp.o

s21_memmove.o: s21_memmove.c
	$(compile) -c $(flags) $(coverFlag) s21_memmove.c -o s21_memmove.o

string_tests.o: string_tests.c
	$(compile) -c $(flags) string_tests.c -o string_tests.o

gcov_report: tests
	./test
	lcov --capture --directory . --output-file=coverage.info
	genhtml coverage.info --output-directory=result
	open ./result/index.html

clean:
	-rm -rf *.o *.gcda *.gcno *result
	