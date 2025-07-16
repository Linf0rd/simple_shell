#include "shell.h"

/**
 * main - The entry point of the Shell.
 *
 * Return: 0 on success.
 */

int main(void)
{
	char *line;
	char **args;
	int status;

	do {
		int i = 0;
		char **cmds = NULL;
		prompt();
		line = read_line();

		/* Remove comments: anything after '#' is ignored */
		for (i = 0; line[i]; i++)
		{
			if (line[i] == '#')
			{
				line[i] = '\0';
				break;
			}
		}

		/* Logical operators: split by ';', '&&', '||' and handle logic */
		int j = 0;
		char *saveptr = NULL;
		char *logic_line = line;
		int last_status = status;

		while (logic_line && *logic_line)
		{
			char *next_and = strstr(logic_line, "&&");
			char *next_or = strstr(logic_line, "||");
			char *next_sep = NULL;
			int do_exec = 1;

			if (next_and && (!next_or || next_and < next_or))
			{
				next_sep = next_and;
				if (last_status != 0)
					do_exec = 0;
			}
			else if (next_or)
			{
				next_sep = next_or;
				if (last_status == 0)
					do_exec = 0;
			}

			char *cmd_chunk;
			if (next_sep)
			{
				size_t chunk_len = next_sep - logic_line;
				cmd_chunk = malloc(chunk_len + 1);
				if (!cmd_chunk)
					break;
				strncpy(cmd_chunk, logic_line, chunk_len);
				cmd_chunk[chunk_len] = '\0';
			}
			else
			{
				cmd_chunk = strdup(logic_line);
				if (!cmd_chunk)
					break;
			}

			/* Remove comments from chunk */
			for (j = 0; cmd_chunk[j]; j++)
			{
				if (cmd_chunk[j] == '#')
				{
					cmd_chunk[j] = '\0';
					break;
				}
			}

			/* Split chunk by ';' for chaining */
			cmds = tokenize(cmd_chunk, ";");
			free(cmd_chunk);
			if (!cmds)
			{
				free(line);
				break;
			}
			for (j = 0; cmds[j] != NULL; j++)
			{
				char *cmd_with_vars = replace_vars(cmds[j], last_status);
				char **args = split_line(cmd_with_vars ? cmd_with_vars : cmds[j], " \t\t");
				if (cmd_with_vars)
					free(cmd_with_vars);
				if (args == NULL)
					continue;
				if (args[0] == NULL)
				{
					free_args(args);
					continue;
				}
				/* Alias expansion: replace first arg with alias value if exists */
				{
					const char *alias_val = get_alias(args[0]);
					if (alias_val)
					{
						free(args[0]);
						args[0] = strdup(alias_val);
					}
				}
				if (do_exec)
					last_status = status = execute(args, args[0]);
				free_args(args);
			}
			for (j = 0; cmds[j] != NULL; j++)
				free(cmds[j]);
			free(cmds);

			if (!next_sep)
				break;
			logic_line = next_sep + 2;
		}
		free(line);
	}
	while (status != 0);

	return (0);
}
