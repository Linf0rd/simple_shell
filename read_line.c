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

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			write(STDOUT_FILENO, "\n", 1);
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
	if (line == NULL)
	{
		fprintf(stderr, "read_line: Null line\n");
		return (NULL);
	}
	return (line);
}
