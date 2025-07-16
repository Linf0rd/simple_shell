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

	/* Betty: variable declarations at top */

	do {
		prompt();
		line = read_line();
		args = split_line(line, " \t\t");
		if (args == NULL)
		{
			free(line);
			continue;
		}
		status = execute(args, args[0]);
		free(line);
		free_args(args);
	}
	while (status != 0);

	return (0);
}
