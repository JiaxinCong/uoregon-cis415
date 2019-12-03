#ifndef THREAD_STRUCTS_H
#define THREAD_STRUCTS_H
#include "thread_safe_bounded_queue.h"
#include <sys/time.h>
#define URLSIZE 500
#define	CAPSIZE 1000


typedef struct topicEntry Entry;

typedef struct line_arguments Argument;

typedef struct timeval Timeval;

struct topicEntry {
	int entryNum;
	Timeval *timeStamp;
	int pubID;
	char photoURL[URLSIZE]; // URL to photo
	char photoCaption[CAPSIZE]; // photo caption
};

struct line_arguments {
	int count;
	char **args;
};

TSBoundedQueue *MallocTopicQueue(long size);

long long TryAddEntry(TSBoundedQueue *queue,void *item); 

int Thread_TryDequeue(TSBoundedQueue *queue,long long id);

long long Thread_GetFront(TSBoundedQueue *queue);

long long Thread_GetBack(TSBoundedQueue *queue);

int Thread_GetCount(TSBoundedQueue *queue);

int Thread_IsIdValid(TSBoundedQueue *queue,long long id);

void *Thread_GetItem(TSBoundedQueue *queue,long long id);

int Thread_IsFull(TSBoundedQueue *queue);

int Thread_IsEmpty(TSBoundedQueue *queue);

void Thread_FreeBoundedQueue(TSBoundedQueue *queue);

Entry *MakeEntry();

#endif
