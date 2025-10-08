#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
    Signal handler for SIGINT (Ctrl+C).
    It clears the current input line and displays a new prompt.
*/
void sigint_handler(int signo) {
    (void)signo;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

/*
    Sets up the signal handlers for the shell.
    - SIGINT (Ctrl+C) is caught to prevent the shell from exiting.
    - SIGTSTP (Ctrl+Z) is ignored to prevent the shell from being suspended.
    - SIGQUIT (Ctrl+\) is also ignored.
*/
void setup_signal_handlers(void) {
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}