#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>      // printf, perror
#include <unistd.h>     // fork, execv
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait, WIFEXITED, WEXITSTATUS

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {
    // TODO: Complete and document
    if (argc != 3) {
        printf("ERROR: no arguments\n");
        return 1;
    }

    const char *word = argv[1];
    const char *filename = argv[2];

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        char *gargs[] = {
            "grep",           
            "-s",             
            "-q",             
            (char *)word,     
            (char *)filename, 
            NULL
        };

        int eret = execv("/usr/bin/grep", gargs);
        if (eret == -1) {
            perror("exec");
            return 1; 
        }
    }

    int status;
    pid_t w = wait(&status);
    if (w == -1) {
        perror("wait");
        return 1;
    }

    if (WIFEXITED(status)) {
        int es = WEXITSTATUS(status);

        if (es == 0) {
            printf("FOUND: %s\n", word);
            return 0;
        } else if (es == 1) {
            printf("NOT FOUND: %s\n", word);
            return 0;  
        } else if (es == 2) {
            printf("ERROR: %s doesn't exist\n", filename);
            return 2;
        } else {
            printf("ERROR: grep exited with status %d\n", es);
            return 2;
        }
    } else {
        printf("ERROR: child process did not exit normally\n");
        return 2;
    }
}
