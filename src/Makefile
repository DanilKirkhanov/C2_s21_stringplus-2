CC = -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=address -g
GCO = -fprofile-arcs -ftest-coverage
HEADER = s21_string.h
SOURCES = $(wildcard ./base/*.c)
LIBRARY = $(patsubst %.c, %.o, $(SOURCES))
TEST_OBJECTS = $(patsubst %.c, %.o, $(TEST_FILE))
SYSTEM_NAME := $(shell uname -s)

%.o: %.c $(HEADER)
	gcc $(СС) -c $< -o $@

ifeq ($(SYSTEM_NAME),Linux)
    OPEN_CMD = xdg-open
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
	BREW = .
endif
ifeq ($(SYSTEM_NAME),Darwin)
	OPEN_CMD = open
	ADD_LIB =
	BREW := ${HOME}/homebrew
endif

PATH := $(BREW)/bin:$(PATH)

all: clean s21_string.a gcov_report test

s21_string.a: $(LIBRARY) $(HEADER)
	ar rcs s21_string.a $(LIBRARY)
	ranlib s21_string.a
	rm -rf ./*/*.o

test: s21_string.a test/string_tests.c
	gcc $(CC) test/string_tests.c s21_string.a -o test.out -lm -lcheck
	./test.out

gcov_report: clean $(SOURCES)
	gcc $(GNO) $(SOURCES) test/string_tests.c -o report_test -lcheck
	./report_test
	lcov -t "report" -o report_test.info -c -d .
	genhtml -o report report_test.info
	$(OPEN_CMD) ./report/index.html

check:
	clang-format -style=Google -n ./*/*.c

clang:
	clang-format -style=Google -i ./*/*.c

rebuild: clean all

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf ./report
