#include "shell.h"
#include "tokenizer.h"

/**
 * get_cmd_path - Get the full path of a command.
 * @cmd: The command to find the path for.
 *
 * Return: The full path of the command, or NULL if not found.
 */

char *get_cmd_path(char *cmd)
{
	char *PATH;
	char **path_tokens;
	struct stat st;
	char *cmd_path;
	int i, j;

	PATH = getenv("PATH");
	path_tokens = NULL;
	cmd_path = NULL;

	if (cmd == NULL || PATH == NULL)
		return (NULL);

	if (strchr(cmd, '/') != NULL)
	{
		if (stat(cmd, &st) == 0)
			return (strdup(cmd));
		else
			return (NULL);
	}

	path_tokens = tokenize(PATH, ":");
	if (!path_tokens)
		return (NULL);

	for (i = 0; path_tokens[i] != NULL; i++)
	{
		cmd_path = malloc(strlen(path_tokens[i]) + strlen(cmd) + 2);
		if (!cmd_path)
		{
			for (j = 0; path_tokens[j] != NULL; j++)
				free(path_tokens[j]);
			free(path_tokens);
			return (NULL);
		}
		strcpy(cmd_path, path_tokens[i]);
		strcat(cmd_path, "/");
		strcat(cmd_path, cmd);
		if (stat(cmd_path, &st) == 0)
		{
			for (j = 0; path_tokens[j] != NULL; j++)
				free(path_tokens[j]);
			free(path_tokens);
			return (cmd_path);
		}
		free(cmd_path);
	}
	for (i = 0; path_tokens[i] != NULL; i++)
		free(path_tokens[i]);
	free(path_tokens);
	return (NULL);
}
