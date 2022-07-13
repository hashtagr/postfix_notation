WWW = -Wall -Wextra -Werror -std=c11
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
LFLAGS=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)

all: calc.a

tests: calc.a
	gcc $(WWW) test.c calc.a -o test
	./test < t.txt
	make clean

test: calc.a
ifeq ($(OS), Darwin)
	gcc $(WWW) unit_test.c calc.a -o unit_test $(LIBS)
	make clean_obj
else
	gcc $(WWW) unit_test.c calc.a -o unit_test $(LIBS) $(LINUX)
	make clean_obj
endif
	./unit_test

gcov_report: clean_test
ifeq ($(OS), Darwin)
	gcc $(WWW) -fprofile-arcs -ftest-coverage unit_test.c polka_calculation.c polka_queue.c polka_stack.c polka_main.c -o unit_test $(LIBS)
else
	gcc $(WWW) -fprofile-arcs -ftest-coverage unit_test.c polka_calculation.c polka_queue.c polka_stack.c polka_main.c -o unit_test $(LIBS) $(LINUX)
endif
	./unit_test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

calc.a: build_calc clean_obj

build_calc:
	gcc $(WWW) -c polka_calculation.c polka_queue.c polka_stack.c polka_main.c
	ar rcs calc.a *.o
	ranlib calc.a

clean_obj:
	rm -rf *.o

clean_lib: 
	rm -rf *.a

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report

clean: clean_lib clean_lib clean_obj clean_test
	rm -rf test
	rm -rf unit_test
