/*
 * CSCI435
 * Assignment 05
 * Adam Sebzda
 */

#define _POSIX_C_SOURCE 200112L
#define _ISOC99_SOURCE
#define __EXTENSIONS__
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define	N_THREADS 6
#define TICKET_MAX 1000


struct threadArg {
	int thread_num;
    struct ticketShared *shared_data;
};

struct ticketShared {
	int	*ticket_counter;
	pthread_mutex_t	*mymutex;
}

void *myWork(void *arg) {
	struct threadArg *args = (struct threadArg *)arg;
    struct ticketShared *shared = (struct ticketShared *)args->shared_data;
	
	for(int i = 0; i < TICKET_MAX; ++i) {
		pthread_mutex_lock(shared->mymutex);
		*(shared->ticket_counter) += 1;
        printf("Ticketing window %d sells a ticket with number %d.\n", *(shared->ticket_counter));
		pthread_mutex_unlock(shared->mymutex);
	}

	pthread_exit(NULL);
}

int main() {
	int	ret;
	pthread_mutex_t mutex;
	pthread_t p[N_THREADS];
	pthread_t p_valid[N_THREADS];
    struct threadArg args[N_THREADS];
	int	p_number = 0;
	int	counter = 0; // shared resource

	struct ticketShared *myShared = (struct ticketShared *) malloc(sizeof(struct ticketShared));
	if(!myShared) {
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	ret = pthread_mutex_init(&mutex, NULL);
	if(ret != 0) {
		fprintf(stderr, "pthread_mutex_init() failed: %s\n", strerror(errno));
		free(myShared);
		return EXIT_FAILURE;
	}

	myShared->mymutex = &mutex;
	myShared->ticket_counter = &counter;

	for(int i = 0; i < N_THREADS; ++i) {
        struct threadArg *myArg = (struct threadArg *) malloc(sizeof(struct threadArg));
        myArg->shared_data = myShared;
        myArg->thread_num = i + 1;
		ret = pthread_create(&p[i], NULL, myWork, myArg);
		if(ret == 0) {
			p_valid[p_number] = p[i];
            args[p_number] = myArg;
			++p_number;
		}
	}

	for(int i = 0; i < p_number; ++i)
		pthread_join(p_valid[i], NULL);

	printf("main thread hopes the couter value is %d\n", 1000 * p_number);
	printf("main thread got the couter value is %d\n", counter);

    for(int i = 0; i < p_number; ++i)
        free(args[i]);

	free(myShared);
	pthread_mutex_destroy(&mutex);

	return EXIT_SUCCESS;
}