#include "shell.h"

/**
 * free_args - Free the memory allocated for the arguments array.
 * @args: The arguments array.
 */

void free_args(char **args)
{
	int x = 0;

	while (args[x])
	{
		if (args[x] != NULL)
			free(args[x]);
		x++;
	}
	free(args);
}
