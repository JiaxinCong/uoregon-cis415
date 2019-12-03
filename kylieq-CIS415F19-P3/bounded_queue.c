#include <stdio.h>
#include <stdlib.h>
#include "bounded_queue.h"

int RoundIDToBufferIndex(int size, long long index) {
        long long value = (index % ((long long)size));
        return (int)value;
}

BoundedQueue *BB_MallocBoundedQueue(long size) {
        struct bounded_queue *returnValue = NULL;
        returnValue = malloc(sizeof(struct bounded_queue)); 
        returnValue->buffer = malloc(size * sizeof(void*)); 
        for(int i = 0; i < size; i++){
                returnValue->buffer[i] = NULL;
        }
        returnValue->size = size;
        returnValue->head = 0;
        returnValue->tail = 0;
        return (BoundedQueue *)returnValue;
}

long long BB_TryEnqueue(struct bounded_queue *queue,void *item) {
        long long returnValue = 0;
        long long head = RoundIDToBufferIndex(queue->size, queue->head);
        if(BB_IsFull(queue) == 0){
                queue->buffer[head] = item;
                returnValue = queue->head;
                queue->head += 1;
        }
        else
                returnValue = -1;

        return returnValue;
}

int BB_TryDequeue(struct bounded_queue *queue,long long id) {
        long long returnValue = -1;
        long long tail = queue->tail;
        if(BB_IsEmpty(queue) == 0){
                if(BB_IsIdValid(queue, id) == 1 && id == tail){
                        queue->buffer[tail] = NULL;
                        queue->tail += 1;
                        returnValue = 1;
                }
        }

        return returnValue;
}

long long BB_GetFront(struct bounded_queue *queue) {
        long long returnValue = -1;
        if(BB_IsEmpty(queue) == 0){
                returnValue = queue->head-1;
        }

        return returnValue;
}

long long BB_GetBack(struct bounded_queue *queue) {
        long long returnValue = -1;
        if(BB_IsEmpty(queue) == 0)
        {
                returnValue = queue->tail;
        }

        return returnValue;
}

int BB_GetCount(struct bounded_queue *queue) {
        long long returnValue = 0;
        returnValue = queue->head - queue->tail;
        return (int)returnValue;
}

int BB_IsIdValid(struct bounded_queue *queue,long long id) {
        long long head = queue->head;
        long long tail = queue->tail;
        int returnValue = 0;
        if(id >= tail && id < head) {
            returnValue = 1;
        }
        else
                returnValue = 0;
        return returnValue;
}

void *BB_GetItem(struct bounded_queue *queue,long long id){
        void *returnValue = NULL;
        if(BB_IsIdValid(queue, id) == 1){
                int newid = RoundIDToBufferIndex(queue->size, id);
                returnValue = queue->buffer[newid];
        }
        return returnValue;
}

int BB_IsFull(struct bounded_queue *queue) { //can possibly just check if head = size and tail = 0
        int returnValue = 0; 
        if((queue->head - queue->tail) == queue->size) {
                returnValue = 1;
        }

        return returnValue;
}

int BB_IsEmpty(struct bounded_queue *queue) {
        int returnValue = 0;
        if(queue->head == queue->tail){
                returnValue = 1;
        }
        return returnValue;
}

void BB_FreeBoundedQueue(struct bounded_queue *queue) {
        free(queue->buffer);
        free(queue);
}