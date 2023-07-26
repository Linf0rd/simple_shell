#include "shell.h"

/**
 * execute - Execute a command.
 * @args: The command and its arguments.
 *
 * Return: 1 on success, 0 on failure.
 */

int execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("#cisfun$");
		return (0);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("#cisfun$");
			return (0);
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
