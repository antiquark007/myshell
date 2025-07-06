#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "executor.h"
#include "builtins.h"

#define MAX_CMD_LEN 1024

int main() {
    char input[MAX_CMD_LEN];

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        if (fgets(input, MAX_CMD_LEN, stdin) == NULL) break;
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) continue;

        // Built-in: exit
        if (is_exit(input)) break;

        // Built-in: cd
        if (handle_cd(input)) continue;

        // Execute command
        execute_input(input);
    }

    return 0;
}
