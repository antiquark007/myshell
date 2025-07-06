#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "parser.h"

int is_exit(const char *input) {
    return strcmp(input, "exit") == 0;
}

int handle_cd(char *input) {
    if (strncmp(input, "cd", 2) != 0) return 0;

    char *args[64];
    parse_input(input, args);

    if (args[1] == NULL) {
        fprintf(stderr, "cd: expected argument\n");
        return 1;
    }

    if (chdir(args[1]) != 0) {
        perror("cd");
    }

    return 1;
}
