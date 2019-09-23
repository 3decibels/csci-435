/*
 * File: fork3.c
 * parent and child process
 * CSCI435
 */

#define _POSIX_C_SOURCE 200112L
#define _ISOC99_SOURCE
#define __EXTENSIONS__
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	pid_t	pid;

	pid = fork();
	if(pid < 0) {
		fprintf(stderr, "fork() failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	else if(pid == 0) {
		int	c = 8;
		int	d = 0;
		printf("%d\n", c / d);
		exit(EXIT_SUCCESS);
	}
	else {
		int	ret;
		pid_t cpid = waitpid(pid, &ret, 0);
		fprintf(stderr, "Parent process %ld, child process %ld\n", (long)getpid(), (long)pid);
		fprintf(stderr, "terminated process %ld\n", (long)cpid);
		if(WIFEXITED(ret))
			fprintf(stderr, "normal termination with status %d\n", WEXITSTATUS(ret));
		else if(WIFSIGNALED(ret))
			fprintf(stderr, "signal termination with sig number %d\n", WTERMSIG(ret));
	}
	return EXIT_SUCCESS;
}
