#ifndef TOPIC_QUEUE_H
#define TOPIC_QUEUE_H
#include <sys/time.h>
#include "synch_bounded_queue.h"
#define	CAPSIZE 500

struct TopicEntry {
	int entryNum;
	struct timeval *timeStamp;
	int pubID;
	char *photoURL; // URL to photo
	char *photoCaption[CAPSIZE]; // photo caption
};

struct SynchBoundedQueue *MallocTopicQueue(long size);

long long Enqueue(struct SynchBoundedQueue *queue,void *entry); 

int Dequeue(struct SynchBoundedQueue *queue,long long id);

void *GetEntry(struct SynchBoundedQueue *queue,long long id);

long long GetBack(struct SynchBoundedQueue *queue);

long long GetFront(struct SynchBoundedQueue *queue); /* Not used in part 1 */

int GetCount(struct SynchBoundedQueue *queue); /* Not used in part 1 */

int ValidEntry(struct SynchBoundedQueue *queue,long long id); /* Not used in part 1 */

int IsFull(struct SynchBoundedQueue *queue); /* Not used in part 1 */

int IsEmpty(struct SynchBoundedQueue *queue); /* Not used in part 1 */

void FreeBoundedQueue(struct SynchBoundedQueue *queue); /* Not used in part 1 */

struct TopicEntry *MakeEntry();

#endif
