#include "shell.h"
#include "tokenizer.h"

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
	char **tokens;

	if (line == NULL)
	{
		fprintf(stderr, "split_line: Null line\n");
		return (NULL);
	}

	tokens = tokenize(line, delim);
	if (!tokens)
	{
		perror("split_line");
		return (NULL);
	}
	return (tokens);
}
