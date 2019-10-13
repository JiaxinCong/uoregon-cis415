CC = gcc
CFLAGS = -g -Wall

default: p1

p1: main.o command.o
	$(CC) $(CFLAGS) -o p1 main.o command.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

clean:
	$(RM) p1 *.o *~
