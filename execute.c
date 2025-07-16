#include "shell.h"

extern char **environ;

/**
 * execute - Execute a command.
 * @args: The command and its arguments.
 * @name: The name of the command.
 *
 * Return: 1 on success, 0 on failure.
 */

int execute(char **args, char *name)
	/* History built-in */
	if (strcmp(args[0], "history") == 0)
	{
		print_history();
		return (1);
	}
	/* Alias built-in */
	if (strcmp(args[0], "alias") == 0)
	{
		if (!args[1])
		{
			print_aliases();
		}
		else if (strchr(args[1], '=') != NULL)
		{
			char *eq = strchr(args[1], '=');
			size_t nlen = eq - args[1];
			char namebuf[128], valbuf[256];
			strncpy(namebuf, args[1], nlen);
			namebuf[nlen] = '\0';
			strcpy(valbuf, eq + 1);
			set_alias(namebuf, valbuf);
		}
		else if (args[1])
		{
			const char *val = get_alias(args[1]);
			if (val)
				printf("alias %s='%s'\n", args[1], val);
		}
		return (1);
	}
{
	pid_t pid;
	int status, x;
	char *cmd_path;

	int in_redirect = -1, out_redirect = -1, append = 0;
	int i, j, argc = 0;
	char *infile = NULL, *outfile = NULL;
	/* Count args */
	while (args[argc]) argc++;
	/* Parse for redirection */
	for (i = 0; i < argc; i++) {
		if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0) {
			append = (strcmp(args[i], ">>") == 0);
			if (args[i+1]) {
				outfile = args[i+1];
				out_redirect = i;
			}
		} else if (strcmp(args[i], "<") == 0) {
			if (args[i+1]) {
				infile = args[i+1];
				in_redirect = i;
			}
		}
	}
	/* Remove redirection tokens from args */
	if (out_redirect != -1) {
		for (j = out_redirect; args[j+2]; j++)
			args[j] = args[j+2];
		args[j] = NULL;
		argc -= 2;
	}
	if (in_redirect != -1) {
		for (j = in_redirect; args[j+2]; j++)
			args[j] = args[j+2];
		args[j] = NULL;
		argc -= 2;
	}
	if (args == NULL || name == NULL)
		return ((args == NULL) ? 0 : -1);

	if (strcmp(args[0], "exit") == 0)
		return (0);

	if (strcmp(args[0], "env") == 0)
	{
		for (x = 0; environ[x] != NULL; x++)
			printf("%s\n", environ[x]);
		return (1);
	}

	if (strcmp(args[0], "setenv") == 0)
	{
		if (args[1] && args[2])
		{
			if (setenv(args[1], args[2], 1) == -1)
				perror("setenv");
		}
		else
		{
			fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		}
		return (1);
	}

	if (strcmp(args[0], "unsetenv") == 0)
	{
		if (args[1])
		{
			if (unsetenv(args[1]) == -1)
				perror("unsetenv");
		}
		else
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		}
		return (1);
	}

	if (strcmp(args[0], "cd") == 0)
	{
		char *dir = args[1];
		if (!dir)
			dir = getenv("HOME");
		if (chdir(dir) == -1)
			perror("cd");
		return (1);
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
		free(cmd_path);
		return (0);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, args, NULL) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", name, args[0]);
			free(cmd_path);
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
