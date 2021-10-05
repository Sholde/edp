CC=gcc
CFLAGS=-Wall
OFLAGS=-O2 -march=native -mtune=native
LFLAGS=-lm

.PHONY: all clean

all: main

main: main.o config.o request.o
	$(CC) $(LFLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $(OFLAGS) $< -o $@

main.o: main.c config.c config.h request.c request.h

config.o: config.c config.h

request.o: config.c config.h request.c request.h

clean:
	rm -Rf *~ *.o main
