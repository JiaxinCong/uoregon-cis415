#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "topic_queue.h"
#include "synch_bounded_queue.h"
#include "bounded_queue.h"
#include "utilities.h" /* Only struct FileLines and function FreeFile used */
#define THREADSIZE 20
#define QUEUESIZE 20

pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // Thread condition variable
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex

int DELTA = 0;

struct ArgStruct {
	int index;
	char *filename;
};

void *Subscriber(void *args){
	struct ArgStruct *arg = args;
	pthread_mutex_lock(&lock);
	pthread_cond_wait(&cond, &lock);
	printf("Proxy thread %u - type: Subscriber\n", (unsigned int)pthread_self());
	printf("Subscriber thread %d reading %s\n", arg->index, (char *)arg->filename);
	pthread_mutex_unlock(&lock); 
	return 0;
}

void *Publisher(void *args) {
	struct ArgStruct *arg = args;
	pthread_mutex_lock(&lock);
	pthread_cond_wait(&cond, &lock);
	printf("Proxy thread %u - type: Publisher\n", (unsigned int)pthread_self());
	printf("Publisher thread %d reading %s\n", arg->index, (char *)arg->filename);
	pthread_mutex_unlock(&lock); 
	return 0;
}

int main(int argc, char *argv[]) {
	struct FileLines* Lines = LoadAFile(argv[1]);
	struct LineArguments **line_arguments = malloc(Lines->LineCount * sizeof(struct LineArguments *));

	for (int i=0; i<Lines->LineCount; i++) {
		line_arguments[i] = malloc(sizeof(struct LineArguments));
	}

	for (int i=0; i<Lines->LineCount; i++) {
		line_arguments[i]->args = malloc(20 * sizeof(char *));

		char *line = strtok(Lines->Lines[i]," \n");

		for (int j = 0; line; j++){
			if (line != NULL) {
				line_arguments[i]->args[j] = malloc(strlen(line)+1);
				strcpy(line_arguments[i]->args[j], line);
			}
			line = strtok(NULL, " \n");
		}
	}

	pthread_t subscriber_threads[THREADSIZE];
	pthread_t publisher_threads[THREADSIZE];
	struct synch_bounded_queue *topic_queues[QUEUESIZE];
	char *topicnames[QUEUESIZE];
	char *subscribernames[THREADSIZE];
	char *publishernames[THREADSIZE];

	int topicCtr = 0;
	int subCtr = 0;
	int pubCtr = 0;

	for (int i=0; i<Lines->LineCount; i++) {
		if (strcmp(line_arguments[i]->args[0], "start") == 0) {
			break;
		}
		else if (strcmp(line_arguments[i]->args[0], "create") == 0) {
			if (strcmp(line_arguments[i]->args[1], "topic") == 0) {
				int size = atoi(line_arguments[i]->args[4]);
				struct synch_bounded_queue *topic_queue = MallocTopicQueue(size);
				topic_queues[topicCtr] = topic_queue;
				topicnames[topicCtr] = line_arguments[i]->args[3];
				topicCtr += 1;
			}
			else if (strcmp(line_arguments[i]->args[1], "subscriber") == 0) {
				struct ArgStruct *args = malloc(sizeof(struct ArgStruct *));
				args->filename = line_arguments[i]->args[2];
				args->index = subCtr;
				subscribernames[subCtr] = line_arguments[i]->args[2];
				pthread_create(&subscriber_threads[subCtr], NULL, Subscriber, (void *)args);
				subCtr += 1;
			}
			else if (strcmp(line_arguments[i]->args[1], "publisher") == 0) {
				struct ArgStruct *args = malloc(sizeof(struct ArgStruct *));
				args->filename = line_arguments[i]->args[2];
				args->index = pubCtr;
				publishernames[pubCtr] = line_arguments[i]->args[2];
				pthread_create(&publisher_threads[pubCtr], NULL, Publisher, (void *)args);
				pubCtr += 1;
			}
		}
		else if (strcmp(line_arguments[i]->args[0], "Delta") == 0) {
			DELTA = atoi(line_arguments[i]->args[1]);
			printf("DELTA %d\n", DELTA);
		}
		else {
			if (strcmp(line_arguments[i]->args[1], "topics") == 0) {
				printf("Topics:\n");
				for(int i = 0; i<topicCtr; i++) {
					//printf("topic %d %d\n", i, topic_queues[i]->queue->size);
					printf("Topic %d %s - size: %d\n", i, topicnames[i], topic_queues[i]->queue->size);
				}
			}
			else if(strcmp(line_arguments[i]->args[1], "subscribers") == 0) {
				printf("Subscribers:\n");
				for(int i = 0; i < subCtr; i++){
					printf("Subscriber thread %d - %s\n", i, subscribernames[i]);
				}
			}
			else if (strcmp(line_arguments[i]->args[1], "publishers") == 0) {
				printf("Publishers:\n");
				for(int i = 0; i < pubCtr; i++){
					printf("Publisher thread %d - %s\n", i, publishernames[i]);
				}
			}
		}
	}

	sleep(5);
	for(int i = 0; i < 20; i++) {
		printf("*****");
	}
	printf("\n");

	pthread_cond_broadcast(&cond);

	int check = 0;
	for (int i=0; i<pubCtr; i++) {
		check += pthread_join(publisher_threads[i], NULL);
	}	
	if (check == 0) {
		printf("All publisher threads have successfully exited.\n");
	}

	check = 0;
	for (int i=0; i<subCtr; i++) {
		check += pthread_join(subscriber_threads[i], NULL);
	}
	if (check == 0) {
		printf("All subscriber threads have successfully exited.\n");
	}

	for (int i=0; i<20; i++) {
		printf("*****");
	}
	printf("\n");

	FreeFile(Lines);
	return 0;
}