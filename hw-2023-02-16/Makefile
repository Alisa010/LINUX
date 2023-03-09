CFLAGS = -Werror -Wall -g --coverage

all: main

test1:
	./main < test1.txt

test2:
	./main < test2.txt

test3:
	./main < test3.txt

main: qsort.o
	gcc $(CFLAGS) qsort.c -o main

qsort.o: qsort.c
	gcc $(CFLAGS) -c qsort.c

coverage:
	lcov -c -d . --rc lcov_branch_coverage=1 -o coverage.info -d .
	genhtml --branch-coverage -o html coverage.info	
clean:
	rm -rf *.o main
