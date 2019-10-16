/******************
 * exam02_7.c
 * Author: Adam Sebzda
 * Class:  CSCI-435
 *****************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    else if (pid > 0) {
        int ret;
        close(fd[0]);
        printf("Parent process goes first\n");
        write(fd[1], 0, 1);
        close(fd[1]);
        wait(&ret);
    }
    else if (pid == 0) {
        // Child PID reads data from pipe
        int nothing;
        close(fd[1]);
        read(fd[0], &nothing, 1);
        printf("Child process goes second\n");
        close(fd[0]);
    }

    return EXIT_SUCCESS;
}
