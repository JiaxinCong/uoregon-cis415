CC = gcc
CFLAGS = -g -Wall

default: part1

part1: part1.o
	$(CC) $(CFLAGS) -o part1 part1.o

part1.o: part1.c
	$(CC) $(CFLAGS) -c part1.c

clean:
	$(RM) part1 *.o *~
