#ifndef THREAD_SAFE_BOUNDED_QUEUE_H
#define THREAD_SAFE_BOUNDED_QUEUE_H
#include <pthread.h> 
#include <unistd.h>
#include "bounded_queue.h"

struct thread_safe_bounded_queue {
	struct bounded_queue *queue;
	pthread_mutex_t lock; 
};

struct thread_safe_bounded_queue *TS_BB_MallocBoundedQueue(long size);

long long TS_BB_Enqueue(struct thread_safe_bounded_queue *queue,void *entry); 

int TS_BB_Dequeue(struct thread_safe_bounded_queue *queue,long long id);

void *TS_BB_GetEntry(struct thread_safe_bounded_queue *queue,long long id);

long long TS_BB_GetBack(struct thread_safe_bounded_queue *queue);

long long TS_BB_GetFront(struct thread_safe_bounded_queue *queue);

int TS_BB_GetCount(struct thread_safe_bounded_queue *queue);

int TS_BB_IsIdValid(struct thread_safe_bounded_queue *queue,long long id);

int TS_BB_IsFull(struct thread_safe_bounded_queue *queue);

int TS_BB_IsEmpty(struct thread_safe_bounded_queue *queue);

void TS_BB_FreeBoundedQueue(struct thread_safe_bounded_queue *queue);

#endif
