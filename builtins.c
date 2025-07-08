#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <readline/history.h>
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

int handle_pwd(char *input) {
    if (strncmp(input, "pwd", 3) != 0) return 0;
    
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
    return 1;
}

int handle_echo(char *input) {
    if (strncmp(input, "echo", 4) != 0) return 0;
    
    char *args[64];
    parse_input(input, args);
    
    for (int i = 1; args[i] != NULL; i++) {
        if (i > 1) printf(" ");
        
        // Basic variable expansion for $HOME, $USER, $PWD
        if (args[i][0] == '$') {
            char *var = getenv(args[i] + 1);
            if (var) {
                printf("%s", var);
            } else {
                printf("%s", args[i]);
            }
        } else {
            printf("%s", args[i]);
        }
    }
    printf("\n");
    return 1;
}

int handle_help(char *input) {
    if (strncmp(input, "help", 4) != 0) return 0;
    
    printf("MyShell - Built-in Commands:\n");
    printf("  cd <dir>     - Change directory\n");
    printf("  pwd          - Print working directory\n");
    printf("  echo <text>  - Display text (supports basic $VAR expansion)\n");
    printf("  help         - Show this help message\n");
    printf("  history      - Display command history\n");
    printf("  alias        - Show aliases (basic implementation)\n");
    printf("  unalias      - Remove aliases (basic implementation)\n");
    printf("  which <cmd>  - Locate command in PATH\n");
    printf("  exit         - Exit the shell\n");
    printf("\nSupported features:\n");
    printf("  - Command execution\n");
    printf("  - I/O redirection (>, <)\n");
    printf("  - Pipes (|)\n");
    printf("  - Command history (with readline)\n");
    return 1;
}

int handle_history_cmd(char *input) {
    if (strncmp(input, "history", 7) != 0) return 0;
    
    HIST_ENTRY **history_list = history_get_history_state()->entries;
    int history_length = history_get_history_state()->length;
    
    for (int i = 0; i < history_length; i++) {
        printf("%4d  %s\n", i + 1, history_list[i]->line);
    }
    return 1;
}

int handle_alias(char *input) {
    if (strncmp(input, "alias", 5) != 0) return 0;
    
    // Basic alias implementation - just show message
    printf("Alias functionality not fully implemented yet.\n");
    printf("Usage: alias name=value\n");
    return 1;
}

int handle_unalias(char *input) {
    if (strncmp(input, "unalias", 7) != 0) return 0;
    
    // Basic unalias implementation - just show message
    printf("Unalias functionality not fully implemented yet.\n");
    printf("Usage: unalias name\n");
    return 1;
}

int handle_which(char *input) {
    if (strncmp(input, "which", 5) != 0) return 0;
    
    char *args[64];
    parse_input(input, args);
    
    if (args[1] == NULL) {
        fprintf(stderr, "which: expected argument\n");
        return 1;
    }
    
    char *path = getenv("PATH");
    if (!path) {
        printf("which: PATH not set\n");
        return 1;
    }
    
    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");
    
    while (dir != NULL) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[1]);
        
        struct stat st;
        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR)) {
            printf("%s\n", full_path);
            free(path_copy);
            return 1;
        }
        dir = strtok(NULL, ":");
    }
    
    printf("which: %s: not found\n", args[1]);
    free(path_copy);
    return 1;
}
