#include "shell.h"

/**
 * split_line - Splits a line into tokens.
 * @line: The line meant to be split.
 *
 * Return: An array of tokens.
 */

char **split_line(char *line, char *delim)
{
	int bufsize = 64;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("#cisfun$");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, " \t\n");
	while (token != NULL)
	{
		tokens[position] = strdup(token);
		position++;
		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("#cisfun$");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delim);
	}
	tokens[position] = NULL;
	return (tokens);
}
