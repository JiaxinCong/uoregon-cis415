#ifndef BOUNDED_QUEUE_H
#define BOUNDED_QUEUE_H

struct bounded_queue {
	void **buffer;
	long long head;
	long long tail;
	int size;
};

struct bounded_queue *BB_MallocBoundedQueue(long size); 

long long BB_Enqueue(struct bounded_queue *queue,void *entry); 

int BB_Dequeue(struct bounded_queue *queue,long long id);

void *BB_GetEntry(struct bounded_queue *queue,long long id);

long long BB_GetBack(struct bounded_queue *queue); 

long long BB_GetFront(struct bounded_queue *queue); 

int BB_GetCount(struct bounded_queue *queue); /* Not used in part 1 */

int BB_IsIdValid(struct bounded_queue *queue,long long id); 

int BB_IsFull(struct bounded_queue *queue);

int BB_IsEmpty(struct bounded_queue *queue); 

void BB_FreeBoundedQueue(struct bounded_queue *queue); /* Not used in part 1 */

#endif
