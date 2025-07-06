#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <readline/readline.h>
#include "prompt.h"

char *get_prompt() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    const char *user = getpwuid(getuid())->pw_name;

    char prompt[2048];
    snprintf(prompt, sizeof(prompt),
        "\001\033[1;32m\002%s@\001\033[1;34m\002%s\001\033[0m\002$ ",
        user, cwd);

    return readline(prompt); // memory allocated, must free later
}
