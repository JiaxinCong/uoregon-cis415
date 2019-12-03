/* Functionality to modify data in queue */
#include <stdio.h>
#include <stdlib.h>
#include "bounded_queue.h"

int RoundIDToBufferIndex(int size, long long index) {
    long long result = (index % ((long long)size));
    return result;
}

struct bounded_queue *BQ_MallocBoundedQueue(long size) {
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

long long BQ_Enqueue(struct bounded_queue *queue, void *entry) {
	// If enqueue valid, return position of head. Otherwise, -1.
	long long result = -1;
	long long head = RoundIDToBufferIndex(queue->size, queue->head);
	if (BQ_IsFull(queue) == 0) { // queue not full
		queue->buffer[head] = entry;
		result = queue->head;
		queue->head += 1;
	}
	return result;
}

int BQ_Dequeue(struct bounded_queue *queue, long long id) {
	// If dequeue valid, return position of tail. Otherwise, -1.
	long long result = -1;
	if (BQ_IsEmpty(queue) == 0) { // queue not empty
		if ((BQ_IsIdValid(queue, id) == 1) && (id == queue->tail)) {
			//free(queue->buffer[queue->tail]);
			queue->buffer[queue->tail] = NULL;
			result = queue->tail;
			queue->tail += 1;
		}
	}
	return result;
}

void *BQ_GetEntry(struct bounded_queue *queue, long long id){
	void *result = NULL;
	if (BQ_IsIdValid(queue, id) == 1) {
		int newid = RoundIDToBufferIndex(queue->size, id);
		result = queue->buffer[newid];
	}
	return result;
}

long long BQ_GetBack(struct bounded_queue *queue) {
	if (BQ_IsEmpty(queue) == 0) {
		return queue->tail;
	}
	return -1;
}

long long BQ_GetFront(struct bounded_queue *queue) {
	long long result = -1;
	if (BQ_IsEmpty(queue) == 0) {
		result = queue->head-1;
	}
	return result;
}

int BQ_GetCount(struct bounded_queue *queue) {
	long long result = queue->head - queue->tail;
	return result;
}

int BQ_IsIdValid(struct bounded_queue *queue, long long id) { 
	long long head = queue->head;
	long long tail = queue->tail;
	if (id >= tail && id < head) {
		return 1;
	}
	return 0;
}

int BQ_IsFull(struct bounded_queue *queue) { 
	if (queue->head == queue->size && queue->tail == 0) {
		return 1;
	}
	return 0;
}

int BQ_IsEmpty(struct bounded_queue *queue) { 
	if (queue->head == queue->tail) {
		return 1;
	}
	return 0;
}

void BQ_FreeBoundedQueue(struct bounded_queue *queue, int size) {
	for(int i = 0; i < size; i++){
		free(queue->buffer[i]);
	}
	free(queue->buffer);
	free(queue);
}