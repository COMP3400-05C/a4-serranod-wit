#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>     // for printf, puts
#include <ctype.h>     // for toupper
#include <string.h>    // for strlen


// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {
 if (argc <= 1) {
        printf("ERROR: No arguments\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        const char* word = argv[i];

        for (int j = 0; j < strlen(word); j++) {
            char c = word[j];
            c = toupper((unsigned char)c);
            printf("%c", c);
        }

        if (i < argc - 1) {
            printf(",");
        }
    }

    printf("\n");
    return 0;
}
