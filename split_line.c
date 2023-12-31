#include "shell.h"

/**
 * split_line - Splits a line into tokens.
 * @line: The line meant to be split.
 *
 * @delim: The delimiter used for splitting the line.
 *
 * Return: An array of tokens.
 */

char **split_line(char *line, char *delim)
{
	int bufsize = 64;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (line == NULL)
	{
		fprintf(stderr, "split_line: Null line\n");
		return (NULL);
	}
	if (!tokens)
	{
		perror("split_line");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, delim);
	while (token != NULL)
	{
		tokens[position] = strdup(token);
		if (tokens[position] == NULL)
		{
			perror("split_line");
			exit(EXIT_FAILURE);
		}
		position++;
		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("split_line");
				free(token);
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delim);
	}
	tokens[position] = NULL;
	return (tokens);
}
