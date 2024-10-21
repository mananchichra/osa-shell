#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include"cd.h"

#define MAX_PATH_LEN 1024

// Variable to store the previous working directory
char prev_dir[MAX_PATH_LEN];

// Helper function to print errors
void print_error(const char *msg) {
    perror(msg);
}

// Function to handle the 'cd' command
void cd_command(char **args) {
    char cwd[MAX_PATH_LEN];  // Buffer to store the current working directory
    char *home = getenv("HOME");  // Get the home directory

    // If 'cd' has more than one argument
    if (args[1] && args[2]) {
        printf("cd: too many arguments\n");
        return;
    }

    // Save the current working directory before changing
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        print_error("getcwd");
        return;
    }

    // If 'cd' is called with no arguments or with '~', go to the home directory
    if (!args[1] || strcmp(args[1], "~") == 0) {
        if (chdir(home) != 0) {
            print_error("cd");
        }
    }
    // If 'cd ..' is called, move one level up
    else if (strcmp(args[1], "..") == 0) {
        if (chdir("..") != 0) {
            print_error("cd");
        }
    }
    // If 'cd -' is called, switch to the previous directory and print it
    else if (strcmp(args[1], "-") == 0) {
        if (strlen(prev_dir) == 0) {
            printf("cd: no previous directory\n");
        } else {
            printf("%s\n", prev_dir);
            if (chdir(prev_dir) != 0) {
                print_error("cd");
            }
        }
    }
    // Otherwise, treat the argument as a directory path
    else {
        if (chdir(args[1]) != 0) {
            print_error("cd");
        }
    }

    // Update the previous directory to the current one before it changes
    strcpy(prev_dir, cwd);
}
