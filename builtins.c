#include "builtins.h"
#include "cd.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

// Print current directory
void builtin_pwd()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("pwd error");
    }
}

// Change directory
void builtin_cd(char *path)
{
    if (path == NULL)
    {
        fprintf(stderr, "Expected argument to \"cd\"\n");
    }
    else if (chdir(path) != 0)
    {
        perror("cd error");
    }
}


void builtin_echo(char **args)
{
    int i = 1;
    int printed_space = 0;
    int flag = 0;
    while (args[i] != NULL)
    {
        char *arg = args[i];
        // Check if the argument is wrapped in quotes
        if (arg[0] == '"' || arg[strlen(arg) - 1] == '"')
        {
            // printf("case 1");
            // Strip the quotes and print exactly as is
            for (int j = 0; j <= strlen(arg) - 1; j++)
            {
                
                if((j == 0 || j == strlen(arg) - 1))
                {
                    if(arg[j] == '"')
                        continue;
                }
                // printf("%c", arg[j]);
                if (isspace(arg[j]))
                {
                    if (!printed_space)
                    {
                        printf(" ");
                        printed_space = 1;
                    }
                }
                else
                {
                    printf("%c", arg[j]);
                    printed_space = 0;
                }

                if(j == 0 || j == strlen(arg) - 2)
                flag = flag^1;
            }
        }
        else
        {
            for (int j = 0; arg[j] != '\0'; j++)
            {
                if (isspace(arg[j]))
                {
                    if (!printed_space)
                    {
                        printf(" ");
                        printed_space = 1;
                    }
                }
                else
                {
                    printf("%c", arg[j]);
                    printed_space = 0;
                }
            }
        }
        if (args[i + 1] != NULL)
        {
            printf(" ");
        }
        i++;
    }

    printf("\n");
}

// Function to handle built-in commands
int handle_builtin_commands(char **args)
{
    if (strcmp(args[0], "pwd") == 0)
    {
        builtin_pwd();
        return 1;
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        cd_command(args);
        return 1;
    }
    else if (strcmp(args[0], "echo") == 0)
    {
        builtin_echo(args);
        return 1;
    }
    return 0;
}
