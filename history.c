#include "history.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_HISTORY 100

static char *history[MAX_HISTORY];
static int history_count = 0;

void add_history(const char *cmd)
{
    if (!cmd || !*cmd)
        return;
    if (history_count == MAX_HISTORY)
    {
        free(history[0]);
        for (int i = 1; i < MAX_HISTORY; i++)
            history[i - 1] = history[i];
        history_count--;
    }
    history[history_count++] = strdup(cmd);
}

void print_history(void)
{
    for (int i = 0; i < history_count; i++)
        printf("%d %s\n", i + 1, history[i]);
}

void free_history(void)
{
    for (int i = 0; i < history_count; i++)
        free(history[i]);
    history_count = 0;
}

const char *get_last_history(void)
{
    if (history_count == 0)
        return NULL;
    return history[history_count - 1];
}
