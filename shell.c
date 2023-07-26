#include "shell.h"

/**
 * main - The entry point of the Shell.
 *
 * Return: 0 on success.
 */

int main(void)
{
	char *line;
	char **args;
	int status;

	do {
		prompt();
		line = read_line();
		args = split_line(line, " \t\n");
		status = execute(args, args[0]);
		free(line);
		free_args(args);
	}

	while (status == 1);

	return (0);
}
