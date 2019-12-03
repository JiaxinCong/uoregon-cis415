/* Outline for topic queue */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "part1.h"
#include "synch_bounded_queue.h"

struct synch_bounded_queue *MallocTopicQueue(long size) {
	struct synch_bounded_queue *result = NULL;
	result = SBQ_MallocBoundedQueue(size);
	return result;
}

long long Enqueue(struct synch_bounded_queue *queue, void *entry) {
	long long result = SBQ_Enqueue(queue, entry);
	return result;
}

int Dequeue(struct synch_bounded_queue *queue,long long id) {
	int result = SBQ_Dequeue(queue, id); 
	return result;
}

void *GetEntry(struct synch_bounded_queue *queue,long long id) {
	void *result = SBQ_GetEntry(queue, id);
	return result;
}

long long GetBack(struct synch_bounded_queue *queue) {
	long long result = SBQ_GetBack(queue);
	return result;
}

long long GetFront(struct synch_bounded_queue *queue) { /* Not used in part 1 */
	long long result = SBQ_GetFront(queue);
	return result;
}

int GetCount(struct synch_bounded_queue *queue) { /* Not used in part 1 */
	long long result = SBQ_GetCount(queue);
	return result;
}

int ValidEntry(struct synch_bounded_queue *queue,long long id) { /* Not used in part 1 */
	int result = SBQ_ValidEntry(queue, id);
	return result;
}

int IsFull(struct synch_bounded_queue *queue) { /* Not used in part 1 */
	int result = SBQ_IsFull(queue); 
	return result;
}

int IsEmpty(struct synch_bounded_queue *queue) { /* Not used in part 1 */
	int result = SBQ_IsEmpty(queue);
	return result;
}

void FreeBoundedQueue(struct synch_bounded_queue *queue) { 
	SBQ_FreeBoundedQueue(queue);
}

struct topicEntry *MakeEntry(int num) {
	struct topicEntry *entry = NULL;
	entry = malloc(sizeof(struct topicEntry));
	entry->entryNum = num;
	entry->timeStamp = NULL;
	entry->pubID = 0;
	entry->photoURL[0] = '\0';
	entry->photoCaption[0] = '\0';
	return entry;
}

int main() {
	int size = 30;
	struct synch_bounded_queue *topic_queue = MallocTopicQueue(size);
	struct topicEntry *entry = NULL;

	int check = 0;
	int ctr = 0;

	/* Fill queue & attempt to enqueue when full */
	for (ctr=0; ctr<size+5; ctr++) {
		entry = MakeEntry(ctr);
		check = Enqueue(topic_queue, entry);
		if (check > -1) {
			printf("Enqueued: %d\n", check);
		}
		else {
			printf("Enqueue Denied\n");
		}
	}

	/* Empty queue & attempt to dequeue when empty */
	for (ctr=0; ctr<size+5; ctr++) {
		int tail = GetBack(topic_queue);
		if (tail >= 0) {
			entry = GetEntry(topic_queue, tail);
			printf("Dequeued: %d\n", entry->entryNum);
			check = Dequeue(topic_queue, tail);
			if (check < 0) {
				printf("Dequeue Denied\n");
			}
		}
		else {
			printf("Dequeue Denied\n");
		}
	}
	FreeBoundedQueue(topic_queue);
	return 0;
}