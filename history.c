#include "history.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HISTORY_FILE ".shell_history"
#define MAX_HISTORY 20
#define DEFAULT_PRINT_HISTORY 10

// Structure to store command history
typedef struct
{
    char *commands[MAX_HISTORY]; // Array to store commands
    int count;                   // Total number of commands entered
    int start;                   // Points to the oldest command
} History;

// Initialize the history structure
History history = {.count = 0, .start = 0};

// Load history from a file
void load_history()
{
    FILE *file = fopen(HISTORY_FILE, "r");
    if (file == NULL)
    {
        return; // No history file exists yet
    }

    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1)
    {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        history.commands[history.count % MAX_HISTORY] = strdup(line);
        history.count++;
    }
    fclose(file);
    if (line)
    {
        free(line);
    }
}

void save_history()
{
    FILE *file = fopen(HISTORY_FILE, "w");
    if (file == NULL)
    {
        perror("Could not open history file");
        return;
    }

    int start = history.count > MAX_HISTORY ? history.count % MAX_HISTORY : 0;
    int total_commands = history.count > MAX_HISTORY ? MAX_HISTORY : history.count;

    for (int i = 0; i < total_commands; i++)
    {
        fprintf(file, "%s\n", history.commands[(start + i) % MAX_HISTORY]);
    }

    fclose(file);
}

// void add_to_history(const char *cmd)
// {

//     if (history.count > 0)
//     {
//         int last_index = (history.count - 1) % MAX_HISTORY;
//         if (strcmp(history.commands[last_index], cmd) == 0)
//         {
//             return; // Don't add the command if it's the same as the last one
//         }

//     }
//     // if (history.commands[history.count % MAX_HISTORY])
//     // {
//     //     free(history.commands[history.count % MAX_HISTORY]); // Free old command if it exists
//     // }
//     // else
//     // {
//     //     history.count++;
//     // }
//     // history.commands[history.count % MAX_HISTORY] = strdup(cmd); // Add new command
//     if (history.commands[history.count % MAX_HISTORY])
//     {
//         free(history.commands[history.count % MAX_HISTORY]); // Free old command if it exists
//     }
//     history.commands[history.count % MAX_HISTORY] = strdup(cmd); // Add new command
//     history.count++;                                             // Increment the count after adding the command

//     save_history();

//     // history.count++;
// }

// Function to trim leading and trailing spaces
char *trim_whitespace(char *str) {
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    // All spaces
    if(*str == 0) return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end+1) = 0;

    return str;
}

void add_to_history(const char *command)
{
    char *cmd = trim_whitespace(strdup(command));

    if (cmd == NULL || strlen(cmd) == 0 || strspn(cmd, " \t\n") == strlen(cmd))
    {
        return; // Don't add empty or whitespace-only commands
    }
    // If history is not empty, check the last command to avoid adding duplicates
    if (history.count > 0)
    {
        int last_index = (history.count - 1) % MAX_HISTORY;
        if (strcmp(history.commands[last_index], cmd) == 0)
        {
            return; // Don't add the command if it's the same as the last one
        }
    }

    // Free the old command if it exists at the current index (for circular history)
    if (history.commands[history.count % MAX_HISTORY])
    {
        free(history.commands[history.count % MAX_HISTORY]);
    }

    // Add the new command and increment the history count
    history.commands[history.count % MAX_HISTORY] = strdup(cmd);
    history.count++;

    // Save the history to the file after adding the new command
    // save_history();

    // Append the new command to the history file immediately
    FILE *file = fopen(HISTORY_FILE, "a");
    if (file != NULL)
    {
        fprintf(file, "%s\n", cmd);
        fclose(file);
    }
    else
    {
        perror("Error opening history file for appending");
    }
}

void print_history()
{
    int start = history.count > MAX_HISTORY ? history.count % MAX_HISTORY : 0;
    int total = history.count > MAX_HISTORY ? MAX_HISTORY : history.count;
    int print_count = total > DEFAULT_PRINT_HISTORY ? DEFAULT_PRINT_HISTORY : total;

    for (int i = total - print_count; i < total; i++)
    {
        printf("%d %s\n", i + 1, history.commands[(start + i) % MAX_HISTORY]);
    }
}

// Function to handle the 'history' command
void history_command(char **args)
{
    print_history();
}
