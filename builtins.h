#ifndef BUILTINS_H
#define BUILTINS_H

int is_exit(const char *input);
int handle_cd(char *input);
int handle_pwd(char *input);
int handle_echo(char *input);
int handle_help(char *input);
int handle_history_cmd(char *input);
int handle_alias(char *input);
int handle_unalias(char *input);
int handle_which(char *input);

#endif
