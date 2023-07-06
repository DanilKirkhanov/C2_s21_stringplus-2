# compile = gcc
# flags = -Wall -Werror -Wextra
# 12 =-lcheck
# coverFlag =--coverage


# all: tests 

# tests: s21_memchr.o s21_memcpy.o s21_memcmp.o string_tests.o s21_memmove.o s21_memset.o s21_strcat.o s21_strncat.o
# 	$(compile) $(flags) $(12) $(coverFlag) s21_memchr.o s21_memcpy.o s21_memcmp.o s21_memmove.o s21_memset.o s21_strcat.o s21_strncat.o string_tests.o -o test

# s21_memchr.o: s21_memchr.c
# 	$(compile) -c $(flags) $(coverFlag) s21_memchr.c -o s21_memchr.o

# s21_memcpy.o: s21_memcpy.c
# 	$(compile) -c $(flags) $(coverFlag) s21_memcpy.c -o s21_memcpy.o

# s21_memcmp.o: s21_memcmp.c
# 	$(compile) -c $(flags) $(coverFlag) s21_memcmp.c -o s21_memcmp.o

# s21_memmove.o: s21_memmove.c
# 	$(compile) -c $(flags) $(coverFlag) s21_memmove.c -o s21_memmove.o

# s21_memset.o: s21_memset.c
# 	$(compile) -c $(flags) $(coverFlag) s21_memset.c -o s21_memset.o

# s21_strcat.o: s21_strcat.c
# 	$(compile) -c $(flags) $(coverFlag) s21_strcat.c -o s21_strcat.o

# s21_strncat.o: s21_strncat.c
# 	$(compile) -c $(flags) $(coverFlag) s21_strncat.c -o s21_strncat.o

# string_tests.o: string_tests.c
# 	$(compile) -c $(flags) string_tests.c -o string_tests.o

# gcov_report: tests
# 	./test
# 	lcov --capture --directory . --output-file=coverage.info
# 	genhtml coverage.info --output-directory=result
# 	open ./result/index.html

# clean:
# 	-rm -rf *.o *.gcda *.gcno *result

CFLAGS = -c -Wall -Werror -Wextra -std=c11
LDFLAGS = -Wall -Werror -Wextra -std=c11
SOURCE = $(wildcard s21_*.c)
OBJECTS = $(patsubst %.c,%.o, ${SOURCE})
TESTS_SOURCE = string_tests.c
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = xdg-open
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	ADD_LIB =
endif

all: clean s21_string.a

s21_string.a: ${SOURCE}
	gcc $(CFLAGS) $(ADD_LIB) $(SOURCE)
	ar rcs $@ $(OBJECTS)
	ranlib s21_string.a
	-rm -rf *.o
main: s21_string.a
	gcc $(LDFLAGS) main_test.c s21_string.a -o main.out -lcheck -lm
	./main.out
test: clean s21_string.a
	gcc $(LDFLAGS) -o test string_tests.c s21_string.a $(ADD_LIB) -lcheck
	./test

clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf s21_test
	-rm -rf RESULT_VALGRIND.txt
	-rm -rf *result coverage.info s21_test.info s21_string.a test

gcov_report:${SOURCE}
	gcc --coverage ${SOURCE} ${TESTS_SOURCE} -o test $(ADD_LIB) -lcheck
	./test
	gcov ${SOURCE}
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

valgrind:
	clean
	make s21_string.a
	gcc -g ${TESTS_SOURCE} s21_math.a -o test -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=RESULT_VALGRIND.txt ./test
	