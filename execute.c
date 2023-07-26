#include "shell.h"

/**
 * execute - Execute a command.
 * @args: The command and its arguments.
 *
 * @name: The name of the command.
 *
 * Return: 1 on success, 0 on failure.
 */

int execute(char **args, char *name)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror(name);
		return (0);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", name, args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		}
	while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}
