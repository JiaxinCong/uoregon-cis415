main1-2: main1-2.c
	gcc -g -std=c99 -o main1-2 main1-2.c topic_queue.c synch_bounded_queue.c bounded_queue.c

part1: part1.c
	gcc -g -std=c99 -o part1 part1.c topic_queue.c synch_bounded_queue.c bounded_queue.c

part2: part2.c
	gcc -g -std=c99 -o part2 part2.c

part3: part3.c
	gcc -g -std=c99 -o part3 part3.c topic_queue.c synch_bounded_queue.c bounded_queue.c utilities.c

clean:
	$(RM) main1-2 *.o *~
	$(RM) part1 *.o *~
	$(RM) part2 *.o *~
	$(RM) part3 *.o *~
