/*
 * File: fork2.c
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

int	g_var = 100;

int main() {
	int	l_var = 1;
	pid_t	pid;

	pid = fork();
	if(pid < 0) {
		fprintf(stderr, "fork() failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	else if(pid == 0) {
		g_var += 1;
		l_var += 1;
		fprintf(stderr, "\tChild process %ld, g_var %d, l_var %d\n", (long)getpid(), g_var, l_var);
		exit(EXIT_SUCCESS);
	}
	else {
		pid_t	cpid;
		int	ret;
		cpid = wait(&ret);
		fprintf(stderr, "Parent process %ld, child process %ld\n", (long)getpid(), (long)pid);
		fprintf(stderr, "g_var %d, l_var %d\n", g_var, l_var);
		fprintf(stderr, "terminated process %ld\n", (long)cpid);
		if(WIFEXITED(ret))
			fprintf(stderr, "normal termination with status %d\n", WEXITSTATUS(ret));
		else if(WIFSIGNALED(ret))
			fprintf(stderr, "signal termination with sig number %d\n", WTERMSIG(ret));
	}
	return EXIT_SUCCESS;
}
