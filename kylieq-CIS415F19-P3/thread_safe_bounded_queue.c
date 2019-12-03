/* Functionality to handle locks */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>
#include "bounded_queue.h"
#include "thread_safe_bounded_queue.h"

struct thread_safe_bounded_queue *TS_BB_MallocBoundedQueue(long size) {
	struct thread_safe_bounded_queue *result = NULL;
    result = malloc(sizeof(struct thread_safe_bounded_queue));
	pthread_mutex_init(&(result->lock), NULL);
	result->queue = BB_MallocBoundedQueue(size);
	return result; 
}

long long TS_BB_Enqueue(struct thread_safe_bounded_queue *queue,void *entry) {
	pthread_mutex_lock(&(queue->lock)); 
	long long result = BB_Enqueue(queue->queue,entry);
	pthread_mutex_unlock(&(queue->lock)); 
	if (result < 0) return -1;
	return result;
}

int TS_BB_Dequeue(struct thread_safe_bounded_queue *queue,long long id) {
	pthread_mutex_lock(&(queue->lock)); 
	int result = BB_Dequeue(queue->queue,id);
	pthread_mutex_unlock(&(queue->lock)); 
	if (result < 0) return -1;
	return result;
}

void *TS_BB_GetEntry(struct thread_safe_bounded_queue *queue,long long id) {
	pthread_mutex_lock(&(queue->lock)); 
	void *result = BB_GetEntry(queue->queue,id);
	pthread_mutex_unlock(&(queue->lock)); 
	return result;
}

long long TS_BB_GetBack(struct thread_safe_bounded_queue *queue) {
	pthread_mutex_lock(&(queue->lock)); 
	long long result = BB_GetBack(queue->queue);
	pthread_mutex_unlock(&(queue->lock)); 
    if (result < 0) return -1;
	return result;
}

long long TS_BB_GetFront(struct thread_safe_bounded_queue *queue) {
    pthread_mutex_lock(&(queue->lock)); 
    long long result = BB_GetFront(queue->queue);
    pthread_mutex_unlock(&(queue->lock)); 
    if (result < 0) return -1;
    return result;
}

int TS_BB_GetCount(struct thread_safe_bounded_queue *queue) {
    long long result = 0;
    pthread_mutex_lock(&(queue->lock)); 
    result = BB_GetCount(queue->queue);
    pthread_mutex_unlock(&(queue->lock)); 
    return result;
}

int TS_BB_IsIdValid(struct thread_safe_bounded_queue *queue,long long id) {
    int result = 0;  
    pthread_mutex_lock(&(queue->lock)); 
    result = BB_IsIdValid(queue->queue,id);
    pthread_mutex_unlock(&(queue->lock)); 
    return result;
}

int TS_BB_IsFull(struct thread_safe_bounded_queue *queue) {
    int result = 0;
    pthread_mutex_lock(&(queue->lock)); 
    result = BB_IsFull(queue->queue);
    pthread_mutex_unlock(&(queue->lock)); 
    return result;
}

int TS_BB_IsEmpty(struct thread_safe_bounded_queue *queue) {
    int result = 0;
    pthread_mutex_lock(&(queue->lock)); 
    result = BB_IsEmpty(queue->queue);
    pthread_mutex_unlock(&(queue->lock)); 
    return result;
}

void TS_BB_FreeBoundedQueue(struct thread_safe_bounded_queue *queue) {
    BB_FreeBoundedQueue(queue->queue);
    queue->queue = NULL;
    pthread_mutex_destroy(&(queue->lock));
    free(queue);
}

