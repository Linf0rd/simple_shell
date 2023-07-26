#include "shell.h"

/**
 * prompt - Displays the Shell prompt.
 */

void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 10);
}
