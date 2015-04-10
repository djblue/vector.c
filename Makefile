bin=main
obj=main.o vector.o

CC=gcc
CFLAGS=-std=c99 -g -O2 -Wall -pedantic

all: $(bin)

$(bin): $(obj)
	$(CC) -o $@ $^
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(obj) $(bin)

test: $(bin)
	@./main # run tests

.PHONY: test
