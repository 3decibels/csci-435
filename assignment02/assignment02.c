/******************
 * assignment02.c
 * Author: Adam Sebzda
 * Class:  CSCI-435
 *****************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE = 4;

int main(int argc, char *argv[]) {
	int fd, bytesRead;
	pid_t pid;
	char buf[BUFFER_SIZE];

	fd = open("./a2", O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Open failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	// Main PID (parent) reads and prints 3 bytes
	bytesRead = read(fd, buffer, BUFFER_SIZE - 1);
	buffer[bytesRead] = '\0';
	printf("I am parent process, I read %s, my PID %ld\n", buffer, (long)getpid());

	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	else if (pid == 0) {
		// Child PID reads and prints 3 bytes
		bytesRead = read(fd, buffer, BUFFER_SIZE - 1);
		buffer[bytesRead] = '\0';
		printf("I am child process, I read %s, my PID %ld\n", buffer, (long)getpid());
	}

	close(fd);
	return EXIT_SUCCESS;
}