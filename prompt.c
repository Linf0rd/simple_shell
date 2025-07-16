#include "shell.h"

/**
 * prompt - Displays the Shell prompt.
 */

void prompt(void)
{
	int written;
	char *custom_prompt = NULL;
	char *color = NULL;

	if (isatty(STDIN_FILENO))
	{
		custom_prompt = getenv("PROMPT");
		color = getenv("PROMPT_COLOR");
		if (color && color[0] != '\0')
		{
			/* Print color code */
			write(STDOUT_FILENO, color, strlen(color));
		}
		if (custom_prompt && custom_prompt[0] != '\0')
		{
			written = write(STDOUT_FILENO, custom_prompt, strlen(custom_prompt));
		}
		else
		{
			written = write(STDOUT_FILENO, "($) ", 4);
		}
		/* Reset color */
		if (color && color[0] != '\0')
		{
			write(STDOUT_FILENO, "\033[0m", 4);
		}
		(void)written;
	}
}
