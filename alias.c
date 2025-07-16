#include "alias.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_ALIASES 128

struct alias_entry {
    char *name;
    char *value;
};

static struct alias_entry aliases[MAX_ALIASES];
static int alias_count = 0;

void set_alias(const char *name, const char *value)
{
    int i;
    for (i = 0; i < alias_count; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            free(aliases[i].value);
            aliases[i].value = strdup(value);
            return;
        }
    }
    if (alias_count < MAX_ALIASES) {
        aliases[alias_count].name = strdup(name);
        aliases[alias_count].value = strdup(value);
        alias_count++;
    }
}

const char *get_alias(const char *name)
{
    int i;
    for (i = 0; i < alias_count; i++) {
        if (strcmp(aliases[i].name, name) == 0)
            return aliases[i].value;
    }
    return NULL;
}

void print_aliases(void)
{
    int i;
    for (i = 0; i < alias_count; i++) {
        printf("alias %s='%s'\n", aliases[i].name, aliases[i].value);
    }
}
