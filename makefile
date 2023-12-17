CC = gcc
CFLAGS = -Wall -std=c99

all: main

main: main.o lib.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c lib.h
	$(CC) $(CFLAGS) -c $<

lib.o: lib.c lib.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o my_program
