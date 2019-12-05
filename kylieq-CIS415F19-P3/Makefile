main: main.c
	gcc -g -std=c99 -o main main.c synch_bounded_queue.c bounded_queue.c

part1: part1.c
	gcc -g -std=c99 -o part1 part1.c synch_bounded_queue.c bounded_queue.c

part2: part2.c
	gcc -g -std=c99 -o part2 part2.c

clean:
	$(RM) main *.o *~
	$(RM) part1 *.o *~
	$(RM) part2 *.o *~
