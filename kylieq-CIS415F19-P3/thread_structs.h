#ifndef THREAD_STRUCTS_H
#define THREAD_STRUCTS_H
#include <sys/time.h>
#include "thread_safe_bounded_queue.h"
#define URLSIZE 500
#define	CAPSIZE 500

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

void *GetEntry(TSBoundedQueue *queue,long long id);

long long GetBack(TSBoundedQueue *queue);

long long GetFront(TSBoundedQueue *queue); /* Not used in part 1 */

int GetCount(TSBoundedQueue *queue); /* Not used in part 1 */

int IsIdValid(TSBoundedQueue *queue,long long id); /* Not used in part 1 */

int IsFull(TSBoundedQueue *queue); /* Not used in part 1 */

int IsEmpty(TSBoundedQueue *queue); /* Not used in part 1 */

void FreeBoundedQueue(TSBoundedQueue *queue); /* Not used in part 1 */

Entry *MakeEntry();

#endif
