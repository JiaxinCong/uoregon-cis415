CC = gcc
CFLAGS = -g -Wall

default: p1

p1: draft1.o command.o
	$(CC) $(CFLAGS) -o p1 draft1.o command.o

draft1.o: draft1.c
	$(CC) $(CFLAGS) -c draft1.c

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

clean:
	$(RM) p1 *.o *~
