/* Functionality to modify data in queue */
#include <stdio.h>
#include <stdlib.h>
#include "bounded_queue.h"

int RoundIDToBufferIndex(int size, long long index) {
    long long result = (index % ((long long)size));
    return result;
}

struct bounded_queue *BB_MallocBoundedQueue(long size) {
    struct bounded_queue *result = NULL;
    result = malloc(sizeof(struct bounded_queue)); 
    result->size = size;
    result->buffer = malloc(size * sizeof(void *)); 
    for (int i=0; i<size; i++) {
        result->buffer[i] = NULL;
    }
    result->head = 0;
    result->tail = 0;
    return result;
}

long long BB_Enqueue(struct bounded_queue *queue,void *entry) {
	long long result = 0;
	long long head = RoundIDToBufferIndex(queue->size, queue->head);
	if (BB_IsFull(queue) == 0) {
		queue->buffer[head] = entry;
		result = queue->head;
		queue->head += 1;
	}
	else {
		result = -1;
	}
	return result;
}

int BB_Dequeue(struct bounded_queue *queue,long long id) {
	long long result = -1;
	long long tail = queue->tail;
	if (BB_IsEmpty(queue) == 0) {
		if (BB_IsIdValid(queue, id) == 1 && id == tail) {
			queue->buffer[tail] = NULL;
			queue->tail += 1;
			result = 1;
		}
	}
	return result;
}

long long BB_GetFront(struct bounded_queue *queue) {
	long long result = -1;
	if (BB_IsEmpty(queue) == 0) {
		result = queue->head-1;
	}
	return result;
}

long long BB_GetBack(struct bounded_queue *queue) {
	long long result = -1;
	if (BB_IsEmpty(queue) == 0) {
		result = queue->tail;
	}
	return result;
}

int BB_GetCount(struct bounded_queue *queue) {
	long long result = 0;
	result = queue->head - queue->tail;
	return result;
}

int BB_IsIdValid(struct bounded_queue *queue,long long id) { 
	long long head = queue->head;
	long long tail = queue->tail;
	int result = 0;
	if (id >= tail && id < head) {
		result = 1;
	}
	else {
		result = 0;
	}
	return result;
}

void *BB_GetEntry(struct bounded_queue *queue,long long id){
	void *result = NULL;
	if (BB_IsIdValid(queue, id) == 1) {
		int newid = RoundIDToBufferIndex(queue->size, id);
		result = queue->buffer[newid];
	}
	return result;
}

int BB_IsFull(struct bounded_queue *queue) { 
	int result = 0; 
	if (queue->head == queue->size && queue->tail == 0) {
		result = 1;
	}
	return result;
}

int BB_IsEmpty(struct bounded_queue *queue) { 
	int result = 0;
	if (queue->head == queue->tail) {
		result = 1;
	}
	return result;
}

void BB_FreeBoundedQueue(struct bounded_queue *queue) {
	free(queue->buffer);
	free(queue);
}