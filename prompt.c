#include "shell.h"

/**
 * prompt - Displays the Shell prompt.
 */

void prompt(void)
{
	int written;

	if (isatty(STDIN_FILENO))
	{
		written = write(STDOUT_FILENO, "($) ", 4);
		(void)written;
	}
}
