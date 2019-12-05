/* Outline for topic queue */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "topic_queue.h"
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
