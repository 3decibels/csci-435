/******************
 * assignment04.c
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

int count = 0;


void handle_sigint(int signum) {
    if (count < 2) {
        count++;
    } else {
        signal(SIGINT, SIG_DFL);
    }
}


int main(int argc, char *argv[]) {
    struct sigaction newaction;
    pid_t x;
    
    newaction.sa_handler = handle_sigint;
    sigemptyset(&newaction.sa_mask);
    newaction.sa_flags = 0;
    for(int i = 0; i < 5; ++i) {
        x = fork();
        if( x == 0 ) {
            sigaction(SIGINT, &newaction, NULL);
            while(1) {
                sleep(100);
            }
        }
    }
    while(1) {
        sleep(100);
    }
}
