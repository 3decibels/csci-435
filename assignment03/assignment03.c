/******************
 * assignment03.c
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
    int fd[2], fsync[2];
    pid_t pid, termPid;
    char buf[32], letter;

    printf("Input a string: ");
    scanf("%31s", buf);

    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    if (pipe(fsync) == -1) {
        fprintf(stderr, "Pipe failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    else if (pid > 0) {
        // Parent PID
        // Prints and feeds data to child PID
        int ret;
        char nothing;
        close(fd[0]);
        close(fsync[1]);
        for (int i = strlen(buf)-1; i >= 0; i = i-2) {
            printf("parent process (PID: %ld) prints %c\n", (long)getpid(), buf[i]);
            if (i-1 >= 0) {
                write(fd[1], &buf[i-1], 1);
                read(fsync[0], &nothing, 1);
            }
        }
        close(fd[1]);
        close(fsync[0]);
        termPid = wait(&ret);
        printf("child process with PID %ld terminates\n", termPid);
    }
    else if (pid == 0) {
        // Child PID reads data from pipe
        char n = 'n';
        close(fd[1]);
        close(fsync[0]);
        while(read(fd[0], &letter, 1) > 0) {
            printf("child process (PID: %ld) prints %c\n", (long)getpid(), letter);
            write(fsync[1], &letter, 1);
        }
        close(fd[0]);
        close(fsync[1]);
    }

    return EXIT_SUCCESS;
}
