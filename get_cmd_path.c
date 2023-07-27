#include "shell.h"

/**
 * get_cmd_path - Get the full path of a command.
 * @cmd: The command to find the path for.
 *
 * Return: The full path of the command, or NULL if not found.
 */

char *get_cmd_path(char *cmd)
{
	char *PATH = getenv("PATH");
	char *path, *paths;
	struct stat st;

	if (cmd == NULL || PATH == NULL)
	{
		return (NULL);
	}
	if (strchr(cmd, '/') != NULL)
	{
		if (stat(cmd, &st) == 0)
		{
			return (strdup(cmd));
		}
		else
		{
			return (NULL);
		}
	}
	paths = strdup(PATH);
	path = strtok(paths, ":");
	while (path != NULL)
	{
		char *cmd_path = malloc(strlen(path) + strlen(cmd) + 2);

		strcpy(cmd_path, path);
		strcat(cmd_path, "/");
		strcat(cmd_path, cmd);
		if (stat(cmd_path, &st) == 0)
		{
			free(paths);
			return (cmd_path);
		}
		free(cmd_path);
		path = strtok(NULL, ":");
	}
	free(paths);
	return (NULL);
}
