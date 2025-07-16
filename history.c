#include "history.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define MAX_HISTORY 100
#define HISTORY_FILE ".simple_shell_history"


static char *history[MAX_HISTORY];
static int history_count = 0;

/* Load history from file */
void load_history(void)
{
    FILE *file = fopen(HISTORY_FILE, "r");
    char line[1024];
    if (!file)
        return;
    while (fgets(line, sizeof(line), file))
    {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        add_history(line);
    }
    fclose(file);
}

/* Save history to file */
void save_history(void)
{
    FILE *file = fopen(HISTORY_FILE, "w");
    int i;
    if (!file)
        return;
    for (i = 0; i < history_count; i++)
        fprintf(file, "%s\n", history[i]);
    fclose(file);
}

void add_history(const char *cmd)
{
    if (!cmd || !*cmd)
        return;
    if (history_count == MAX_HISTORY)
    {
        int i;
        free(history[0]);
        for (i = 1; i < MAX_HISTORY; i++)
            history[i - 1] = history[i];
        history_count--;
    }
    history[history_count++] = strdup(cmd);
}

void print_history(void)
{
    int i;
    for (i = 0; i < history_count; i++)
        printf("%d %s\n", i + 1, history[i]);
}

void free_history(void)
{
    int i;
    for (i = 0; i < history_count; i++)
        free(history[i]);
    history_count = 0;
}

const char *get_last_history(void)
{
    if (history_count == 0)
        return NULL;
    return history[history_count - 1];
}
