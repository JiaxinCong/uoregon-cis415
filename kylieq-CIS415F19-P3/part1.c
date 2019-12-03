/* Outline for Topic Queue */
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

long long Enqueue(struct thread_safe_bounded_queue *queue, void *entry) {
	long long returnValue = TS_BB_Enqueue(queue,entry);
	return returnValue;
}

int Dequeue(struct thread_safe_bounded_queue *queue,long long id) {
        int  returnValue = TS_BB_Dequeue(queue, id); 
        return returnValue;
}

long long GetFront(struct thread_safe_bounded_queue *queue) { /* Not used in part 1 */
        long long returnValue = TS_BB_GetFront(queue);
        return returnValue;
}

long long GetBack(struct thread_safe_bounded_queue *queue) {
        long long returnValue = TS_BB_GetBack(queue);
        return returnValue;
}

int GetCount(struct thread_safe_bounded_queue *queue) { /* Not used in part 1 */
	long long returnValue = TS_BB_GetCount(queue);
	return returnValue;
}

int IsIdValid(struct thread_safe_bounded_queue *queue,long long id) { /* Not used in part 1 */
        int returnValue = TS_BB_IsIdValid(queue, id);
        return returnValue;
}

void *GetEntry(struct thread_safe_bounded_queue *queue,long long id) {
        void *returnValue = TS_BB_GetEntry(queue,id);
        return returnValue;
}

int IsFull(struct thread_safe_bounded_queue *queue) { /* Not used in part 1 */
        int returnValue = TS_BB_IsFull(queue); 
        return returnValue;
}

int IsEmpty(struct thread_safe_bounded_queue *queue) { /* Not used in part 1 */
        int returnValue = TS_BB_IsEmpty(queue);
        return returnValue;
}

void FreeBoundedQueue(struct thread_safe_bounded_queue *queue) { /* Not used in part 1 */
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
	int ctr = 0;
	char *test = NULL;

	/* Fill queue */
	for (ctr = 0; ctr < size; ctr++) {
		Entry *entry = MakeEntry(ctr);
		check = Enqueue(topic_queue, entry);
		printf("Enqueued: %d\n", check);
		if (check < 0) {
			printf("Enqueue Denied\n");
		}
	}

	/* Attempt to fill queue past limit */
	test = "Success";
	Entry *entry = MakeEntry(ctr);
	check = Enqueue(topic_queue, entry);
	printf("Enqueued: %d\n", check);
	if (check < 0) {
		printf("Enqueue Denied\n");
	}
	printf("Test Case: Enqueue when queue is full - Result: %s\n", test);

	/* Empty queue */
	for (ctr = 0; ctr < size; ctr++) {
		int tail = GetBack(topic_queue);
		if (tail >= 0) {
			Entry *output = GetEntry(topic_queue, tail);
			printf("Dequeued: %d\n", output->entryNum);
			check = Dequeue(topic_queue, tail);
			if (check < 0) {
				printf("Dequeue Denied\n");
				test = "Fail";
			}
		}
		else {
			printf("Tail Denied\n");
			test = "Fail";
		}
	}

	/* Attempt to remove item from empty queue */
	test = "Success";
	int tail = GetBack(topic_queue);
	if (tail >= 0) {
		Entry *output = GetEntry(topic_queue, tail);
		printf("Dequeued: %d\n", output->entryNum);
		check = Dequeue(topic_queue, tail);
		if (check < 0) {
			printf("Dequeue Denied\n");
			test = "Fail";
		}
	}
	else {
		printf("Tail Denied\n");
		test = "Fail";
	}
	printf("Test Case: Dequeue when queue is empty - Result: %s\n", test);
}