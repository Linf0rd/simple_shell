#include "shell.h"

/**
 * execute - Execute a command.
 * @args: The command and its arguments.
 * @name: The name of the command.
 *
 * Return: 1 on success, 0 on failure.
 */

int execute(char **args, char *name)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (args == NULL || name == NULL)
	{
		return ((args == NULL) ? 0 : -1);
	}
	if (strcmp(args[0], "exit") == 0)
	{
		return (0);
	}
	cmd_path = get_cmd_path(args[0]);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", name, args[0]);
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, args, NULL) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", name, args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(cmd_path);
	return (1);
}
