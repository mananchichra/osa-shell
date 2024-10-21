#ifndef BUILTINS_H
#define BUILTINS_H

#ifndef PATH_MAX
#define PATH_MAX 4096  // You can adjust this depending on your system
#endif

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 64
#endif

// Function to handle built-in commands
int handle_builtin_commands(char **args);

// Built-in command functions
void builtin_pwd();
void builtin_cd(char *path);
void builtin_echo(char **args);

#endif
