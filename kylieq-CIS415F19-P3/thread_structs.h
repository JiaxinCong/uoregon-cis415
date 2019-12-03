#ifndef THREAD_STRUCTS_H
#define THREAD_STRUCTS_H
#include "thread_safe_bounded_queue.h"
#include <sys/time.h>
#define URLSIZE 500
#define	CAPSIZE 1000


typedef struct topicEntry Entry;

typedef struct line_arguments Argument;

typedef struct timeval timeval;

struct topicEntry {
	int entryNum;
	struct timeval *timeStamp;
	int pubID;
	char photoURL[URLSIZE]; // URL to photo
	char photoCaption[CAPSIZE]; // photo caption
};

struct line_arguments {
	int count;
	char **args;
};

TSBoundedQueue *MallocTopicQueue(long size);

long long Enqueue(TSBoundedQueue *queue,void *entry); 

int Dequeue(TSBoundedQueue *queue,long long id);

long long GetFront(TSBoundedQueue *queue);

long long GetBack(TSBoundedQueue *queue);

int GetCount(TSBoundedQueue *queue);

int IsIdValid(TSBoundedQueue *queue,long long id);

void *GetEntry(TSBoundedQueue *queue,long long id);

int IsFull(TSBoundedQueue *queue);

int IsEmpty(TSBoundedQueue *queue);

void FreeBoundedQueue(TSBoundedQueue *queue);

Entry *MakeEntry();

#endif
