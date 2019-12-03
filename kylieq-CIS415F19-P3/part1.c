/*
This file serves as the outline for the Topic Queue
Implements the Thread Safe Queue header files to help maintain
A circular bounded buffer
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "thread_structs.h"
#include "thread_safe_bounded_queue.h"
#include <sys/time.h>
#define QUACKSIZE 500
#define	CAPTIONSIZE 1000

TSBoundedQueue *MallocTopicQueue(long size) {
	struct thread_safe_bounded_queue *returnValue = NULL;
	returnValue = TS_BB_MallocBoundedQueue(size);
	return (TSBoundedQueue *)returnValue;
}

long long TryAddEntry(struct thread_safe_bounded_queue *queue, void *item) {
	long long returnValue = TS_BB_TryEnqueue(queue,item);
	return returnValue;
}

int Thread_TryDequeue(struct thread_safe_bounded_queue *queue,long long id) {
        int  returnValue = TS_BB_TryDequeue(queue, id); 
        return returnValue;
}

long long Thread_GetFront(struct thread_safe_bounded_queue *queue) {
        long long returnValue = TS_BB_GetFront(queue);
        return returnValue;
}

long long Thread_GetBack(struct thread_safe_bounded_queue *queue) {
        long long returnValue = TS_BB_GetBack(queue);
        return returnValue;
}

int Thread_GetCount(struct thread_safe_bounded_queue *queue) {
	long long returnValue = TS_BB_GetCount(queue);
	return returnValue;
}

int Thread_IsIdValid(struct thread_safe_bounded_queue *queue,long long id) {
        int returnValue = TS_BB_IsIdValid(queue, id);
        return returnValue;
}

void *Thread_GetItem(struct thread_safe_bounded_queue *queue,long long id) {
        void *returnValue = TS_BB_GetItem(queue,id);
        return returnValue;
}

int Thread_IsFull(struct thread_safe_bounded_queue *queue) {
        int returnValue = TS_BB_IsFull(queue); 
        return returnValue;
}

int Thread_IsEmpty(struct thread_safe_bounded_queue *queue) {
        int returnValue = TS_BB_IsEmpty(queue);
        return returnValue;
}

void Thread_FreeBoundedQueue(struct thread_safe_bounded_queue *queue) {
	TS_BB_FreeBoundedQueue(queue);
}

Entry *MakeEntry(int num) {
	struct topicEntry *returnValue = NULL;
	returnValue = (struct topicEntry*)malloc(sizeof(struct topicEntry));
	returnValue->entryNum = num;
	returnValue->timeStamp = NULL;
	returnValue->pubID = 0;
	returnValue->photoURL[0] = '\0';
	returnValue->photoCaption[0] = '\0';

	return returnValue;
}

int main() {
	int size = 30;
	TSBoundedQueue *topic_queue = MallocTopicQueue(size);
	int check = 0;
//	int dequeue_bounds_check = 0;
//	int empty_check = 0;
//	int enqueue_bounds_check = 0;
//	int fill_check = 0;
//	int refill_check = 0;
//	int remove_check = 0;
//	int size_check = 0;
	void *invalid_entry = NULL;
//	printf("size: %d\n", topic_queue->queue->size);

	/* Fill queue past limit */
	for(int i = 0; i < size+5; i++){ //fill the queue overflow of 5; should print 5 fails
		Entry *entry = MakeEntry(i);
		check = TryAddEntry(topic_queue, entry);
		printf("enqueued: %d\n", check);
		if(check < 0){
			printf("Enqueue Denied\n");
			enqueue_bounds_check += 1;
		}
	}

	/* Check if queue is full */
	fill_check = Thread_IsFull(topic_queue);
	printf("isFull: %d\n", check);

	/* Empty Queue past limit */
	for(int i = 0; i < size+7; i++){ //empty the queue overflow of 7, should print 7 fails
		int tail = Thread_GetBack(topic_queue);
		if(tail >= 0){
			Entry *output = Thread_GetItem(topic_queue, tail); //grabbing all of the items and outputting their entrynumber
			printf("dequeued: %d\n", output->entryNum);
			check = Thread_TryDequeue(topic_queue, tail);
			if(check < 0){
				printf("Dequeue Denied\n");
			}
		}
		else{
			printf("Tail Denied\n");
			dequeue_bounds_check += 1;
		}
	}

	/* Check if queue is empty */
	empty_check = Thread_IsEmpty(topic_queue);
	printf("isEmpty: %d\n", check);
	
	/* Fill queue past limit again */
	for(int i = 0; i < size; i++){ //fill the queue overflow of 5; should print 5 fails
		Entry *entry = MakeEntry(i);
		check = TryAddEntry(topic_queue, entry);
		printf("enqueued: %d\n", check);
		if(check < 0){
			printf("Enqueue Denied\n");
		}
	}

	/* Check if queue is full */
	refill_check = Thread_IsFull(topic_queue);

	/* Remove some items from the queue */
	for(int i = 0; i < 30; i++){ //deletes some items from queue
		int tail = Thread_GetBack(topic_queue);
		if(tail >= 0){
			Entry *output = Thread_GetItem(topic_queue, tail);
			printf("dequeued: %d\n", output->entryNum);
			check = Thread_TryDequeue(topic_queue, tail);
			if(check < 0){
				printf("Dequeue Denied\n");
			}
		}
		else{
			printf("Tail Denied\n");
		}
	}

	size_check = Thread_GetCount(topic_queue);

	invalid_entry = Thread_GetItem(topic_queue, size*2); //attempting to access an item not in the queue

	/*
	Printing Results From Tests!
	*/
	int pass = 0;
	for(int i = 0; i < 20; i++)
		printf("*****");
	printf("\n");
	if(fill_check == 1){
		printf("FILL QUEUE CHECK: PASSES\n");
		pass += 1;
	}
	else
		printf("FILL QUEUE CHECK: FAILS\n");
	if(enqueue_bounds_check == 5){
		printf("ENQUEUE BOUNDS CHECK: PASSES\n");
		pass += 1;
	}
	else
		printf("ENQUEUE BOUNDS CHECK: FAILS\n");
	if(empty_check == 1){
		printf("EMPTY QUEUE CHECK: PASSES\n");
		pass += 1;
	}
	else
		printf("EMPTY QUEUE CHECK: FAILS\n");
	if(dequeue_bounds_check == 7){
		printf("DEQUEUE BOUNDS CHECK: PASSES\n");
		pass += 1;
	}
	else
		printf("DEQUEUE BOUNDS CHECK: FAILS\n");
	if(refill_check == 1){
		printf("REFILL QUEUE CHECK: PASSES\n");
		pass += 1;
	}
	else
		printf("REFILL QUEUE CHECK: FAILS\n");
	if(size_check == (size-30)){
		printf("DELETE ITEMS CHECK: PASSES %d REMAINING of size: %d\n", size_check, size);
		pass += 1;
	}
	else
		printf("DELETE ITEMS CHECK: FAILS %d %d\n", size_check, size);
	if(invalid_entry == NULL){
		printf("INVALID GET ENTRY CHECK: PASSES\n");
		pass += 1;
	}
	else
		printf("INVALID GET ENTRY CHECK: FAILS\n");

	if(pass == 7)
		printf("ALL TEST CASES PASSED: ALL 9 REQUIREMENTS FULFILLED\n");
	else
		printf("ONLY %d/7 TEST CASES PASSED\n", pass);

	for(int i = 0; i < 20; i++)
		printf("*****");
	printf("\n");
}