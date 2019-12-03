/* Outline for topic queue */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "thread_structs.h"
#include "thread_safe_bounded_queue.h"

struct thread_safe_bounded_queue *MallocTopicQueue(long size) {
	struct thread_safe_bounded_queue *result = NULL;
	result = TS_BB_MallocBoundedQueue(size);
	return result;
}

long long Enqueue(struct thread_safe_bounded_queue *queue, void *entry) {
	long long result = TS_BB_Enqueue(queue, entry);
	return result;
}

int Dequeue(struct thread_safe_bounded_queue *queue,long long id) {
	int result = TS_BB_Dequeue(queue, id); 
	return result;
}

void *GetEntry(struct thread_safe_bounded_queue *queue,long long id) {
	void *result = TS_BB_GetEntry(queue, id);
	return result;
}

long long GetBack(struct thread_safe_bounded_queue *queue) {
	long long result = TS_BB_GetBack(queue);
	return result;
}

long long GetFront(struct thread_safe_bounded_queue *queue) { /* Not used in part 1 */
	long long result = TS_BB_GetFront(queue);
	return result;
}

int GetCount(struct thread_safe_bounded_queue *queue) { /* Not used in part 1 */
	long long result = TS_BB_GetCount(queue);
	return result;
}

int IsIdValid(struct thread_safe_bounded_queue *queue,long long id) { /* Not used in part 1 */
	int result = TS_BB_IsIdValid(queue, id);
	return result;
}

int IsFull(struct thread_safe_bounded_queue *queue) { /* Not used in part 1 */
	int result = TS_BB_IsFull(queue); 
	return result;
}

int IsEmpty(struct thread_safe_bounded_queue *queue) { /* Not used in part 1 */
	int result = TS_BB_IsEmpty(queue);
	return result;
}

void FreeBoundedQueue(struct thread_safe_bounded_queue *queue) { /* Not used in part 1 */
	TS_BB_FreeBoundedQueue(queue);
}

struct topicEntry *MakeEntry(int num) {
	struct topicEntry *entry = NULL;
	entry = (struct topicEntry*)malloc(sizeof(struct topicEntry));
	entry->entryNum = num;
	entry->timeStamp = NULL;
	entry->pubID = 0;
	entry->photoURL[0] = '\0';
	entry->photoCaption[0] = '\0';
	return entry;
}

int main() {
	int size = 30;
	struct thread_safe_bounded_queue *topic_queue = MallocTopicQueue(size);
	struct topicEntry *entry = NULL;

	int check = 0;
	int ctr = 0;

	/* Fill queue & attempt to enqueue when full */
	for (ctr = 0; ctr < size+5; ctr++) {
		entry = MakeEntry(ctr);
		check = Enqueue(topic_queue, entry);
		printf("Enqueued: %d\n", check);
		if (check < 0) {
			printf("Enqueue Denied\n");
		}
	}

	/* Empty queue & attempt to dequeue when empty */
	for (ctr = 0; ctr < size+5; ctr++) {
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
			printf("Tail Denied\n");
		}
	}
	free(entry);
	FreeBoundedQueue(topic_queue);
}