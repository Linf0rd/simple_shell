#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include <sys/stat.h>
#include "var_replace.h"
#include "tokenizer.h"
#include "alias.h"

char **split_line(char *line, char *delim);
void prompt(void);
int execute(char **args, char *name);
char *read_line(void);
char *get_cmd_path(char *cmd);
void free_args(char **args);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

#endif /* SHELL_H */
