#ifndef THREAD_SAFE_BOUNDED_QUEUE_H
#define THREAD_SAFE_BOUNDED_QUEUE_H
#include <pthread.h> 
#include <unistd.h>
#include "bounded_queue.h"

struct thread_safe_bounded_queue {
	struct bounded_queue *queue;
	pthread_mutex_t lock; 
};

struct thread_safe_bounded_queue *TS_BQ_MallocBoundedQueue(long size);

long long TS_BQ_Enqueue(struct thread_safe_bounded_queue *queue,void *entry); 

int TS_BQ_Dequeue(struct thread_safe_bounded_queue *queue,long long id);

void *TS_BQ_GetEntry(struct thread_safe_bounded_queue *queue,long long id);

long long TS_BQ_GetBack(struct thread_safe_bounded_queue *queue);

long long TS_BQ_GetFront(struct thread_safe_bounded_queue *queue);

int TS_BQ_GetCount(struct thread_safe_bounded_queue *queue);

int TS_BQ_IsIdValid(struct thread_safe_bounded_queue *queue,long long id);

int TS_BQ_IsFull(struct thread_safe_bounded_queue *queue);

int TS_BQ_IsEmpty(struct thread_safe_bounded_queue *queue);

void TS_BQ_FreeBoundedQueue(struct thread_safe_bounded_queue *queue);

#endif
