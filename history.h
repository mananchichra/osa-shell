// #ifndef HISTORY_H
// #define HISTORY_H

// // Maximum number of commands in history
// #define MAX_HISTORY 100

// // Function declarations
// void add_to_history(char *command);
// void display_history();

// #endif
#ifndef HISTORY_COMMAND_H
#define HISTORY_COMMAND_H

#include <ctype.h>

void load_history();
void save_history();
void add_to_history(const char *cmd);
void print_history();
void history_command(char **args);

#endif
