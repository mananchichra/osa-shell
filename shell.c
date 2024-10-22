#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
// #include </usr/include/x86_64-linux-gnu/bits/local_lim.h>
#include <pwd.h>
#include "builtins.h"
#include "history.h"

char *get_username()
{
    struct passwd *pw = getpwuid(getuid());
    return pw->pw_name;
}

// Function to get the system name
char *get_system_name()
{
    static char hostname[HOST_NAME_MAX];
    gethostname(hostname, sizeof(hostname));
    return hostname;
}

// Function to get current directory
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
// Function to display the shell prompt
char *display_prompt()
{
    char cwd[PATH_MAX];          // Buffer to store the current working directory
    char *home = getenv("HOME"); // Get the home directory

    char shell_dir[PATH_MAX];
    getcwd(shell_dir, sizeof(shell_dir));

    // Get the current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        // Check if the current directory is inside the home directory
        if (strstr(cwd, home) == cwd)
        {
            // If cwd starts with home, replace the home part with ~
            printf("~%s$ ", cwd + strlen(home));
        }
        else
        {
            // If cwd is not in the home directory, display full path
            printf("%s$ ", cwd);
        }
    }
    else
    {
        perror("getcwd() error");
    }
}

// Function to read command from user
char *read_command()
{
    // printf("hiii");
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

// Function to split a line into arguments
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

// Main loop of the shell
void shell_loop()
{

    char *command;
    char **args;
    int status = 1;

    do
    {
        // Display the shell prompt
        // printf("%s@%s:%s$ ", get_username(), get_system_name(), get_current_dir());
        printf("%s@%s:", get_username(), get_system_name());
        display_prompt();

        // Read the command from user
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
    load_history();
    // Run the shell loop
    shell_loop();
    return 0;
}

// #endif