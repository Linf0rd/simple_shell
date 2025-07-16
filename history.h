#ifndef HISTORY_H
#define HISTORY_H

void add_history(const char *cmd);
void print_history(void);
void free_history(void);
const char *get_last_history(void);

#endif /* HISTORY_H */
