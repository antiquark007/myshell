#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "parser.h"

void run_command(char **args) {
    for (int i = 0; args[i]; i++) {
        if (strcmp(args[i], ">") == 0 && args[i+1]) {
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        } else if (strcmp(args[i], "<") == 0 && args[i+1]) {
            int fd = open(args[i+1], O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
        }
    }

    execvp(args[0], args);
    perror("exec");
    exit(1);
}

void handle_pipe(char *input) {
    char *left = strtok(input, "|");
    char *right = strtok(NULL, "|");

    if (!right) return;

    int pipefd[2];
    pipe(pipefd);

    pid_t p1 = fork();
    if (p1 == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]); close(pipefd[1]);
        char *args[64];
        parse_input(left, args);
        run_command(args);
    }

    pid_t p2 = fork();
    if (p2 == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]); close(pipefd[0]);
        char *args[64];
        parse_input(right, args);
        run_command(args);
    }

    close(pipefd[0]); close(pipefd[1]);
    wait(NULL); wait(NULL);
}

void execute_input(char *input) {
    if (strchr(input, '|')) {
        handle_pipe(input);
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {
        char *args[64];
        parse_input(input, args);
        run_command(args);
    } else {
        wait(NULL);
    }
}
