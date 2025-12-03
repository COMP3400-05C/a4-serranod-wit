#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>   // for execv, write
#include <stdio.h>    // for perror

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {
    if (argc <= 1) {
        const char *msg = "ERROR: no arguments\n";
        write(1, msg, 20);
        return 1;
    }

    int n = argc - 1;


    char *eargs[4];
    eargs[0] = "echo";

    if (n % 2 == 1) {
        int mid = n / 2;               
        eargs[1] = (char *)argv[1 + mid];
        eargs[2] = NULL;
    } else {
        int mid2 = n / 2;               
        int mid1 = mid2 - 1;            
        eargs[1] = (char *)argv[1 + mid1];
        eargs[2] = (char *)argv[1 + mid2];
        eargs[3] = NULL;
    }

    int eret = execv("/bin/echo", eargs);
    if (eret == -1) {
        perror("exec");
        return 1;
    }

    return 0;
}
