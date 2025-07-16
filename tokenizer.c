#include "shell.h"
#include "tokenizer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * tokenize - Splits a string into tokens using custom logic (no strtok).
 * @line: The input string to tokenize.
 * @delim: Delimiter characters.
 *
 * Return: Array of token strings (must be freed by caller), or NULL on error.
 */
char **tokenize(const char *line, const char *delim)
{
	int bufsize = 64, position = 0, i = 0, start = 0;
	char **tokens = NULL;
	char *token = NULL, *copy = NULL;

	if (!line || !delim)
		return (NULL);

	tokens = malloc(bufsize * sizeof(char *));
	if (!tokens)
		return (NULL);

	copy = strdup(line);
	if (!copy)
	{
		free(tokens);
		return (NULL);
	}

	while (copy[i])
	{
		if (strchr(delim, copy[i]))
		{
			if (i > start)
			{
				copy[i] = '\0';
				token = strdup(copy + start);
				if (!token)
				{
					free(copy);
					for (int j = 0; j < position; j++)
						free(tokens[j]);
					free(tokens);
					return (NULL);
				}
				tokens[position++] = token;
				if (position >= bufsize)
				{
					bufsize += 64;
					char **new_tokens = realloc(tokens, bufsize * sizeof(char *));
					if (!new_tokens)
					{
						free(copy);
						for (int j = 0; j < position; j++)
							free(tokens[j]);
						free(tokens);
						return (NULL);
					}
					tokens = new_tokens;
				}
			}
			start = i + 1;
		}
		i++;
	}
	if (i > start)
	{
		token = strdup(copy + start);
		if (!token)
		{
			free(copy);
			for (int j = 0; j < position; j++)
				free(tokens[j]);
			free(tokens);
			return (NULL);
		}
		tokens[position++] = token;
	}
	free(copy);
	tokens[position] = NULL;
	return (tokens);
}
