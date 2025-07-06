#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "executor.h"
#include "builtins.h"
#include "prompt.h"
#include "history.h"

int main() {
    char *input;

    while (1) {
        input = get_prompt();  // custom prompt with readline

        if (!input) break; // Ctrl+D
        if (strlen(input) == 0) {
            free(input);
            continue;
        }

        add_to_history(input);  // save to history

        if (is_exit(input)) {
            free(input);
            break;
        }

        if (handle_cd(input)) {
            free(input);
            continue;
        }

        execute_input(input);
        free(input);
    }

    return 0;
}
