#ifndef BOUNDED_QUEUE_H
#define BOUNDED_QUEUE_H

struct bounded_queue {
	void **buffer;
	long long head;
	long long tail;
	int size;
};

typedef struct bounded_queue BoundedQueue;

BoundedQueue *BB_MallocBoundedQueue(long size);

long long BB_Enqueue(BoundedQueue *queue,void *entry); 

int BB_Dequeue(BoundedQueue *queue,long long id);

long long BB_GetFront(BoundedQueue *queue);

long long BB_GetBack(BoundedQueue *queue);

int BB_GetCount(BoundedQueue *queue);

int BB_IsIdValid(BoundedQueue *queue,long long id);

void *BB_GetEntry(BoundedQueue *queue,long long id);

int BB_IsFull(BoundedQueue *queue);

int BB_IsEmpty(BoundedQueue *queue);

void BB_FreeBoundedQueue(BoundedQueue *queue);

#endif
