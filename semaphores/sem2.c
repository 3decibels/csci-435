/*
 * File: sem2.c
 * sem example
 * CSCI435
 */

#define _POSIX_C_SOURCE 200112L
#define _ISOC99_SOURCE
#define __EXTENSIONS__
#define _XOPEN_SOURCE 600

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>

int main() {
	sem_t	*my_sem1 = sem_open("/CSCI435sem1", 0);
	if(my_sem1 == SEM_FAILED) {
		fprintf(stderr, "sem_open failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	sem_t   *my_sem2 = sem_open("/CSCI435sem2", 0);
	if(my_sem2 == SEM_FAILED) {
		fprintf(stderr, "sem_open failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	while(1) {
		sem_wait(my_sem2);	// will go first because CSCI435sem2 has value 1 initially
					// starting from the next iteration,
					// process BBB will wait for AAA to post sem2
		printf("I am the user BBB, I am using the semaphore CSCI435sem2\n");
                sleep(1);
		sem_post(my_sem1);
	}
	return EXIT_SUCCESS;
}
