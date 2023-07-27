#include "shell.h"

/**
 * free_args  - Free the memory allocated for the arguments array.
 * @args: The arguments array.
 */

void free_args(char **args)
{
	int x = 0;

	if (args == NULL)
	{
		fprintf(stderr, "free_args: Null argument\n");
		return;
	}
	while (args[x])
	{
		free(args[x]);
		x++;
	}
	free(args);
}
