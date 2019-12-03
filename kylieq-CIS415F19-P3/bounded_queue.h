#ifndef BOUNDED_QUEUE_H
#define BOUNDED_QUEUE_H

struct bounded_queue {
	void **buffer;
	long long head;
	long long tail;
	int size;
};

struct bounded_queue *BQ_MallocBoundedQueue(long size); 

long long BQ_Enqueue(struct bounded_queue *queue,void *entry); 

int BQ_Dequeue(struct bounded_queue *queue,long long id);

void *BQ_GetEntry(struct bounded_queue *queue,long long id);

long long BQ_GetBack(struct bounded_queue *queue); 

long long BQ_GetFront(struct bounded_queue *queue); 

int BQ_GetCount(struct bounded_queue *queue); /* Not used in part 1 */

int BQ_IsIdValid(struct bounded_queue *queue,long long id); 

int BQ_IsFull(struct bounded_queue *queue);

int BQ_IsEmpty(struct bounded_queue *queue); 

void BQ_FreeBoundedQueue(struct bounded_queue *queue, int size); /* Not used in part 1 */

#endif
