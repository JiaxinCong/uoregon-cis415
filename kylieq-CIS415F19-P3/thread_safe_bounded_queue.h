#ifndef THREAD_SAFE_BOUNDED_QUEUE_H
#define THREAD_SAFE_BOUNDED_QUEUE_H
#include "bounded_queue.h"
#include <pthread.h> 
#include <unistd.h>

struct thread_safe_bounded_queue {
        BoundedQueue *queue;
        pthread_mutex_t lock; 
};

typedef struct thread_safe_bounded_queue TSBoundedQueue;

TSBoundedQueue *TS_BB_MallocBoundedQueue(long size);

long long TS_BB_Enqueue(TSBoundedQueue *queue,void *entry); 

int TS_BB_Dequeue(TSBoundedQueue *queue,long long id);

long long TS_BB_GetFront(TSBoundedQueue *queue);

long long TS_BB_GetBack(TSBoundedQueue *queue);

int TS_BB_GetCount(TSBoundedQueue *queue);

int TS_BB_IsIdValid(TSBoundedQueue *queue,long long id);

void *TS_BB_GetEntry(TSBoundedQueue *queue,long long id);

int TS_BB_IsFull(TSBoundedQueue *queue);

int TS_BB_IsEmpty(TSBoundedQueue *queue);

void TS_BB_FreeBoundedQueue(TSBoundedQueue *queue);

#endif
