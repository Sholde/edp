CC=gcc
CFLAGS=-Wall -std=c99
OFLAGS=-O2 -march=native -mtune=native
LFLAGS=-lm

INC=../libstats

.PHONY: all clean

TARGET=main

all: $(TARGET)

$(TARGET): $(TARGET).o tests.o $(INC)/stats.o
	$(CC) $(LFLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $(OFLAGS) -I$(INC) $< -o $@

tests.c: tests.h $(INC)/stats.c $(INC)/stats.h

$(INC)/stats.c: $(INC)/stats.h

clean:
	rm -Rf *~ *.o $(TARGET) $(INC)/*~ $(INC)/*.o
