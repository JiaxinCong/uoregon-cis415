#ifndef SYNCH_BOUNDED_QUEUE_H
#define SYNCH_BOUNDED_QUEUE_H
#include <pthread.h> 
#include <unistd.h>
#include "bounded_queue.h"

struct synch_bounded_queue {
	struct bounded_queue *queue;
	pthread_mutex_t lock; 
};

struct synch_bounded_queue *SBQ_MallocBoundedQueue(long size);

long long SBQ_Enqueue(struct synch_bounded_queue *queue,void *entry); 

int SBQ_Dequeue(struct synch_bounded_queue *queue,long long id);

void *SBQ_GetEntry(struct synch_bounded_queue *queue,long long id);

long long SBQ_GetBack(struct synch_bounded_queue *queue);

long long SBQ_GetFront(struct synch_bounded_queue *queue);

int SBQ_GetCount(struct synch_bounded_queue *queue);

int SBQ_ValidEntry(struct synch_bounded_queue *queue,long long id);

int SBQ_IsFull(struct synch_bounded_queue *queue);

int SBQ_IsEmpty(struct synch_bounded_queue *queue);

void SBQ_FreeBoundedQueue(struct synch_bounded_queue *queue);

#endif
