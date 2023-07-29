#include "shell.h"

/**
 * read_line - Read a line from the user.
 *
 * Return: The line that was entered by the user.
 */

char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;

	characters_read = get_line(&line, &bufsize, stdin);
	if (characters_read == -1)
	{
		if (feof(stdin))
		{
			if (line != NULL)
			{
				free(line);
			}
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("read_line");
			if (line != NULL)
			{
				free(line);
			}
			exit(EXIT_FAILURE);
		}
	}
	if (characters_read > 0 && line[characters_read - 1] == '\n')
	{
		line[characters_read - 1] = '\0';
	}

	return (line);
}
