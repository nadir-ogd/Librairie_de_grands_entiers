CC = gcc
CFLAGS = -Wall -std=c99 -g -Iinclude/
OPT = -O3
SRC = main.c $(wildcard src/*.c)

OBJ = $(patsubst main.o, obj/main.o, $(patsubst src/%, obj/%, $(patsubst %.c, %.o, $(SRC))))

main: $(OBJ)
	$(CC) $^ $(OPT) -o $@ -lm

obj/%.o: src/%.c include/%.h
	$(CC) -c $< $(CFLAGS) -o $@

obj/main.o: main.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f obj/*.o src/*~ include/*~ main

.PHONY: clean