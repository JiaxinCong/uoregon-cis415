#ifndef THREAD_STRUCTS_H
#define THREAD_STRUCTS_H
#include <sys/time.h>
#include "thread_safe_bounded_queue.h"
#define URLSIZE 500
#define	CAPSIZE 500

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

struct thread_safe_bounded_queue *MallocTopicQueue(long size);

long long Enqueue(struct thread_safe_bounded_queue *queue,void *entry); 

int Dequeue(struct thread_safe_bounded_queue *queue,long long id);

void *GetEntry(struct thread_safe_bounded_queue *queue,long long id);

long long GetBack(struct thread_safe_bounded_queue *queue);

long long GetFront(struct thread_safe_bounded_queue *queue); /* Not used in part 1 */

int GetCount(struct thread_safe_bounded_queue *queue); /* Not used in part 1 */

int IsIdValid(struct thread_safe_bounded_queue *queue,long long id); /* Not used in part 1 */

int IsFull(struct thread_safe_bounded_queue *queue); /* Not used in part 1 */

int IsEmpty(struct thread_safe_bounded_queue *queue); /* Not used in part 1 */

void FreeBoundedQueue(struct thread_safe_bounded_queue *queue); /* Not used in part 1 */

struct topicEntry *MakeEntry();

#endif
