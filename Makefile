bin=main

all: main 


main: main.o vector.o ; gcc main.o vector.o -o $(bin)
main.o: vector.h main.c ; gcc main.c -std=c99 -c
vector.o: vector.h vector.c ; gcc -std=c99 vector.c -c

clean: ; rm -f *.o $(bin)

test: main ; @./main # run tests

.PHONY: test
