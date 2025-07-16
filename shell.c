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

	load_history();
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
				{
					free(line);
					break;
				}
				strncpy(cmd_chunk, logic_line, chunk_len);
				cmd_chunk[chunk_len] = '\0';
			}
			else
			{
				cmd_chunk = strdup(logic_line);
				if (!cmd_chunk)
				{
					free(line);
					break;
				}
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
				char *cmd_to_run = cmds[j];
				/* Support !! for last command */
				if (strcmp(cmds[j], "!!") == 0)
				{
					const char *last = get_last_history();
					if (last)
						cmd_to_run = (char *)last;
					else
						continue;
				}
				add_history(cmd_to_run);
				char *cmd_with_vars = replace_vars(cmd_to_run, last_status);
				char **args = split_line(cmd_with_vars ? cmd_with_vars : cmd_to_run, " \t\t");
				if (cmd_with_vars)
					free(cmd_with_vars);
				if (args == NULL)
				{
					/* Handle empty or invalid input */
					continue;
				}
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
				/* Edge case: background job support */
				int run_bg = 0;
				int last_arg = 0;
				while (args[last_arg + 1])
					last_arg++;
				if (args[last_arg] && strcmp(args[last_arg], "&") == 0)
				{
					run_bg = 1;
					free(args[last_arg]);
					args[last_arg] = NULL;
				}
				if (do_exec)
				{
					if (run_bg)
					{
						/* Run in background: fork and do not wait */
						pid_t pid = fork();
						if (pid == 0)
						{
							execute(args, args[0]);
							exit(0);
						}
						else if (pid > 0)
						{
							printf("[background pid %d]\n", pid);
						}
						else
						{
							perror("fork");
						}
						last_status = status;
					}
					else
					{
						last_status = status = execute(args, args[0]);
					}
				}
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

	save_history();
	free_history();
	return (0);
}
