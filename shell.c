#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
// #include </usr/include/x86_64-linux-gnu/bits/local_lim.h>
#include <pwd.h>
#include "builtins.h"
#include "history.h"

char *home = "/home/mananchichra/a3";
// char *home = getenv("PWD");
// char *home;

char *get_username()
{
    struct passwd *pw = getpwuid(getuid());
    return pw->pw_name;
}

char *get_system_name()
{
    static char hostname[HOST_NAME_MAX];
    gethostname(hostname, sizeof(hostname));
    return hostname;
}

char *get_current_dir()
{
    // shell_dir[PATH_MAX];
    // getcwd(shell_dir, sizeof(shell_dir));

    static char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {

        return cwd;
    }
    else
    {
        perror("getcwd() error");
        return NULL;
    }
}
void display_prompt()
{
    char cwd[PATH_MAX];          // Buffer to store the current working directory
    // char *home = getenv("HOME"); // Get the home directory

   

    char shell_dir[PATH_MAX];
    getcwd(shell_dir, sizeof(shell_dir));

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        if (strstr(cwd, home) == cwd)
        {
            printf("~%s$ ", cwd + strlen(home));
        }
        else
        {
            printf("%s$ ", cwd);
        }
    }
    else
    {
        perror("getcwd() error");
    }

    return;
}

char *read_command()
{
    // printf("hiii");
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

char **parse_command(char *line)
{
    int bufsize = 64, position = 0;
    char **tokens = (char **)malloc(bufsize * sizeof(char *));
    char *token;

    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[position++] = token;

        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = (char **)realloc(tokens, bufsize * sizeof(char *));
        }
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

void shell_loop()
{

    char *command;
    char **args;
    int status = 1;

    do
    {
        // printf("%s@%s:%s$ ", get_username(), get_system_name(), get_current_dir());
        printf("%s@%s:", get_username(), get_system_name());
        display_prompt();

        command = read_command();
        // add_to_history(command);
        // Parse the command

        add_to_history(command);
        
        args = parse_command(command);

        // If no command, continue
        if (args[0] == NULL)
        {
            free(command);
            free(args);
            continue;
        }

        // add_to_history(command);

        if (strcmp(command, "exit") == 0)
        {
            save_history();
            break;
        }
        // Handle built-in commands
        if (handle_builtin_commands(args))
        {
            free(command);
            free(args);
            continue;
        }

        // Handle the 'history' command
        if (strcmp(args[0], "history") == 0)
        {
            history_command(NULL);
            free(command);
            free(args);
            continue;
        }

        // Free memory
        free(command);
        free(args);

    } while (status);
}

int main(int argc, char **argv)
{
    // home = getenv("PWD");
    load_history();
    // Run the shell loop
    shell_loop();
    return 0;
}

// #endif