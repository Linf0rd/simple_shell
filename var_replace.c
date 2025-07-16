#include "var_replace.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/**
 * replace_vars - Replace shell variables in a command string.
 * @cmd: The input command string.
 * @last_status: The last exit status ($?).
 *
 * Return: A newly allocated string with variables replaced.
 */
char *replace_vars(const char *cmd, int last_status)
{
	char *result, *p, *env, numbuf[16];
	int len = 0, i = 0;
	pid_t pid = getpid();

	if (!cmd)
		return (NULL);

	result = malloc(strlen(cmd) * 2 + 32);
	if (!result)
		return (NULL);

	p = result;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			if (cmd[i + 1] == '?')
			{
				snprintf(numbuf, sizeof(numbuf), "%d", last_status);
				strcpy(p, numbuf);
				p += strlen(numbuf);
				i += 2;
				continue;
			}
			else if (cmd[i + 1] == '$')
			{
				snprintf(numbuf, sizeof(numbuf), "%d", (int)pid);
				strcpy(p, numbuf);
				p += strlen(numbuf);
				i += 2;
				continue;
			}
			else if (cmd[i + 1] == '{')
			{
				int var_start = i + 2, var_len = 0;
				while (cmd[var_start + var_len] && cmd[var_start + var_len] != '}')
					var_len++;
				if (cmd[var_start + var_len] == '}')
				{
					char varname[128];
					if (var_len > 127)
						var_len = 127;
					strncpy(varname, cmd + var_start, var_len);
					varname[var_len] = '\0';
					env = getenv(varname);
					if (env)
					{
						strcpy(p, env);
						p += strlen(env);
					}
					i += 2 + var_len + 1;
					continue;
				}
			}
			else if ((cmd[i + 1] >= 'A' && cmd[i + 1] <= 'Z') ||
					 (cmd[i + 1] >= 'a' && cmd[i + 1] <= 'z') ||
					 (cmd[i + 1] == '_'))
			{
				int var_start = i + 1, var_len = 0;
				while ((cmd[var_start + var_len] >= 'A' && cmd[var_start + var_len] <= 'Z') ||
					   (cmd[var_start + var_len] >= 'a' && cmd[var_start + var_len] <= 'z') ||
					   (cmd[var_start + var_len] >= '0' && cmd[var_start + var_len] <= '9') ||
					   (cmd[var_start + var_len] == '_'))
					var_len++;
				char varname[128];
				if (var_len > 127)
					var_len = 127;
				strncpy(varname, cmd + var_start, var_len);
				varname[var_len] = '\0';
				env = getenv(varname);
				if (env)
				{
					strcpy(p, env);
					p += strlen(env);
				}
				i += 1 + var_len;
				continue;
			}
		}
		*p++ = cmd[i++];
	}
	*p = '\0';
	return (result);
}
