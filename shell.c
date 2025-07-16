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
		int i = 0;
		char **cmds = NULL;
		prompt();
		line = read_line();

		/* Remove comments: anything after '#' is ignored */
		for (i = 0; line[i]; i++)
		{
			if (line[i] == '#')
			{
				line[i] = '\0';
				break;
			}
		}

		/* Split line by ';' for command chaining */
		cmds = tokenize(line, ";");
		if (!cmds)
		{
			free(line);
			continue;
		}
		for (i = 0; cmds[i] != NULL; i++)
		{
			char *cmd_with_vars = replace_vars(cmds[i], status);
			char **args = split_line(cmd_with_vars ? cmd_with_vars : cmds[i], " \t\t");
			if (cmd_with_vars)
				free(cmd_with_vars);
			if (args == NULL)
				continue;
			if (args[0] == NULL)
			{
				free_args(args);
				continue;
			}
			status = execute(args, args[0]);
			free_args(args);
		}
		for (i = 0; cmds[i] != NULL; i++)
			free(cmds[i]);
		free(cmds);
		free(line);
	}
	while (status != 0);

	return (0);
}
