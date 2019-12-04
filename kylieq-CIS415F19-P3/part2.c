#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // Thread condition variable
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex

void *Subscriber(void *arg) {
	pthread_mutex_lock(&lock);
	pthread_cond_wait(&cond, &lock); // block until condition var cond is broadcast to
	printf("Proxy thread %u - type: %s\n", (unsigned int)pthread_self(), (char*)arg);
	pthread_mutex_unlock(&lock);
	return 0;
}

void *Publisher(void *arg) {
	pthread_mutex_lock(&lock);
	pthread_cond_wait(&cond, &lock); // block until condition var cond is broadcast to
	printf("Proxy thread %u - type: %s\n", (unsigned int)pthread_self(), (char*)arg);
	pthread_mutex_unlock(&lock);
	return 0;
}

void *Cleanup(void *arg) {
	pthread_mutex_lock(&lock);
	pthread_cond_wait(&cond, &lock); // block until condition var cond is broadcast to
	printf("Proxy thread %u - type: %s\n", (unsigned int)pthread_self(), (char*)arg);
	pthread_mutex_unlock(&lock);
	return 0;
}

int main(int argc, char *argv[]) {
	pthread_t subscriber, publisher, cleanup;

	char *arg1 = "Subscriber";
	char *arg2 = "Publisher";
	char *arg3 = "Cleanup";

	// Create threads
	int result1 = pthread_create(&subscriber, NULL, Subscriber, arg1);
	int result2 = pthread_create(&publisher, NULL, Publisher, arg2);	
	int result3 = pthread_create(&cleanup, NULL, Cleanup, arg3);

	sleep(1);

	// Unblock threads blocked on condition var cond
	pthread_cond_broadcast(&cond);

	// Wait for threads to terminate
	int check1 = pthread_join(subscriber, NULL);
	int check2 = pthread_join(publisher, NULL);
	int check3 = pthread_join(cleanup, NULL);

	if (check1 == 0 && check2 == 0 && check3 == 0) {
		printf("All threads have successfully terminated.\n");
	}

	return 0;
}