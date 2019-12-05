#ifndef TOPIC_QUEUE_H
#define TOPIC_QUEUE_H
#include <sys/time.h>
#include "synch_bounded_queue.h"
#define URLSIZE 500
#define	CAPSIZE 500

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

typedef struct line_arguments Argument;

struct synch_bounded_queue *MallocTopicQueue(long size);

long long Enqueue(struct synch_bounded_queue *queue,void *entry); 

int Dequeue(struct synch_bounded_queue *queue,long long id);

void *GetEntry(struct synch_bounded_queue *queue,long long id);

long long GetBack(struct synch_bounded_queue *queue);

long long GetFront(struct synch_bounded_queue *queue); /* Not used in part 1 */

int GetCount(struct synch_bounded_queue *queue); /* Not used in part 1 */

int ValidEntry(struct synch_bounded_queue *queue,long long id); /* Not used in part 1 */

int IsFull(struct synch_bounded_queue *queue); /* Not used in part 1 */

int IsEmpty(struct synch_bounded_queue *queue); /* Not used in part 1 */

void FreeBoundedQueue(struct synch_bounded_queue *queue); /* Not used in part 1 */

struct topicEntry *MakeEntry();

#endif
