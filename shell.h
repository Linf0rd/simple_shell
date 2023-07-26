#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

char **split_line(char *line, char *delim);
void prompt(void);
int execute(char **args, char *name);
void free_args(char **args);
char *read_line(void);
#endif /* SHELL_H */
