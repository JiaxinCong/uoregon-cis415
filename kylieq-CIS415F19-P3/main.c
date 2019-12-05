/* Part 1 & 2 combined */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "part1.h"
#include "synch_bounded_queue.h"

pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // Thread condition variable
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex

int CTR = 0;

//struct topicEntry *entry;
struct synch_bounded_queue *topic_queue;

void *Subscriber(void *arg) {
	pthread_mutex_lock(&lock);
	pthread_cond_wait(&cond, &lock); // block until condition var cond is broadcast to
	printf("Proxy thread %u - type: %s\n", (unsigned int)pthread_self(), (char*)arg);

	int check = 0;
	int tail = GetBack(topic_queue);
	if (tail >= 0) {
		struct topicEntry *entry = GetEntry(topic_queue, tail);
		printf("Dequeued: %d\n", entry->entryNum);
		check = Dequeue(topic_queue, tail);
		if (check < 0) {
			printf("Dequeue Denied\n");
		}
	}
	else {
		printf("Dequeue Denied\n");
	}

	pthread_mutex_unlock(&lock);
	return 0;
}

struct topicEntry *entry;

void *Publisher(void *arg) {
	pthread_mutex_lock(&lock);
	pthread_cond_wait(&cond, &lock); // block until condition var cond is broadcast to
	printf("Proxy thread %u - type: %s\n", (unsigned int)pthread_self(), (char*)arg);
	
	int check = 0;
	struct topicEntry *entry = MakeEntry(CTR);
	check = Enqueue(topic_queue, entry);
	if (check > -1) {
		printf("Enqueued: %d\n", check);
	}
	else {
		printf("Enqueue Denied\n");
	}
	pthread_mutex_unlock(&lock);
	CTR++;
	return 0;
}

struct synch_bounded_queue *MallocTopicQueue(long size) {
	struct synch_bounded_queue *result = NULL;
	result = SBQ_MallocBoundedQueue(size);
	return result;
}

long long Enqueue(struct synch_bounded_queue *queue, void *entry) {
	long long result = SBQ_Enqueue(queue, entry);
	return result;
}

int Dequeue(struct synch_bounded_queue *queue,long long id) {
	int result = SBQ_Dequeue(queue, id); 
	return result;
}

void *GetEntry(struct synch_bounded_queue *queue,long long id) {
	void *result = SBQ_GetEntry(queue, id);
	return result;
}

long long GetBack(struct synch_bounded_queue *queue) {
	long long result = SBQ_GetBack(queue);
	return result;
}

long long GetFront(struct synch_bounded_queue *queue) { /* Not used in part 1 */
	long long result = SBQ_GetFront(queue);
	return result;
}

int GetCount(struct synch_bounded_queue *queue) { /* Not used in part 1 */
	long long result = SBQ_GetCount(queue);
	return result;
}

int ValidEntry(struct synch_bounded_queue *queue,long long id) { /* Not used in part 1 */
	int result = SBQ_ValidEntry(queue, id);
	return result;
}

int IsFull(struct synch_bounded_queue *queue) { /* Not used in part 1 */
	int result = SBQ_IsFull(queue); 
	return result;
}

int IsEmpty(struct synch_bounded_queue *queue) { /* Not used in part 1 */
	int result = SBQ_IsEmpty(queue);
	return result;
}

void FreeBoundedQueue(struct synch_bounded_queue *queue) { 
	SBQ_FreeBoundedQueue(queue);
}

struct topicEntry *MakeEntry(int num) {
	struct topicEntry *entry = NULL;
	entry = malloc(sizeof(struct topicEntry));
	entry->entryNum = num;
	entry->timeStamp = NULL;
	entry->pubID = 0;
	entry->photoURL[0] = '\0';
	entry->photoCaption[0] = '\0';
	return entry;
}

int main() {
	int size = 30;
	topic_queue = MallocTopicQueue(size);

	int ctr = 0;

	char *arg1 = "Subscriber";
	char *arg2 = "Publisher";

	// Create threads
	pthread_t subscriber, publisher;

	for (int i=0; i<=30; i++) {
		pthread_create(&publisher, NULL, Publisher, arg2);
	}

	for (int i=0; i<=30; i++) {
		pthread_create(&subscriber, NULL, Subscriber, arg1);
	}

	// Unblock threads blocked on condition var cond
	pthread_cond_broadcast(&cond);
	sleep(5);

	// Wait for threads to terminate
	int check = 0;
	check += pthread_join(subscriber, NULL);
	check += pthread_join(publisher, NULL);

	if (check == 0) {
		printf("All threads have successfully terminated.\n");
	}

	FreeBoundedQueue(topic_queue);
	return 0;
}