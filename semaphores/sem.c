/*
 * File: sem.c
 * sem creation exmaple
 * must compiled with -lpthread
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


int main() {
	/* unlink those semophares first before creation */
	sem_unlink("/CSCI435sem1");
	sem_unlink("/CSCI435sem2");

	sem_t	*my_sem1 = sem_open("/CSCI435sem1", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
	if(my_sem1 == SEM_FAILED) {
		fprintf(stderr, "sem_open failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	sem_t   *my_sem2 = sem_open("/CSCI435sem2", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	if(my_sem2 == SEM_FAILED) {
		fprintf(stderr, "sem_open failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	while(1) {
		sem_wait(my_sem1);	// will wait at first because my_sem1 is 0
					// will also wait in the future for BBB to post sem1
		printf("I am the user AAA, I am now using semaphore CSCI435sem1\n");
                sleep(1);
		sem_post(my_sem2);	// tell process BBB to go
	}

	return EXIT_SUCCESS;
}
