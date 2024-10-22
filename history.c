#include "history.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// // Global history array and counter
// char *history[MAX_HISTORY];
// int history_count = 0;

// // Function to add commands to history
// void add_to_history(char *command) {
//     if (history_count < MAX_HISTORY) {
//         history[history_count++] = strdup(command);
//     }
// }

// // Function to display the command history
// void display_history() {
//     for (int i = 0; i < history_count; i++) {
//         printf("%d %s\n", i + 1, history[i]);
//     }
// }
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

// Save history to a file
// void save_history()
// {
//     FILE *file = fopen(HISTORY_FILE, "w");
//     if (file == NULL)
//     {
//         perror("Could not open history file");
//         return;
//     }
//     int history_start = history.count > MAX_HISTORY ? history.count % MAX_HISTORY : 0;
//     int total_commands = history.count > MAX_HISTORY ? MAX_HISTORY : history.count;

//     for (int i = 0; i < total_commands; i++)
//     {
//         fprintf(file, "%s\n", history.commands[(history_start + i) % MAX_HISTORY]);
//     }

//     fclose(file);
// }

void save_history() {
    FILE *file = fopen(HISTORY_FILE, "w");
    if (file == NULL) {
        perror("Could not open history file");
        return;
    }

    int start = history.count > MAX_HISTORY ? history.count % MAX_HISTORY : 0;
    int total_commands = history.count > MAX_HISTORY ? MAX_HISTORY : history.count;

    for (int i = 0; i < total_commands; i++) {
        fprintf(file, "%s\n", history.commands[(start + i) % MAX_HISTORY]);
    }

    fclose(file);
}

// Add a command to the history
void add_to_history(const char *cmd)
{

    if (history.count > 0)
    {
        int last_index = (history.count - 1) % MAX_HISTORY;
        if (strcmp(history.commands[last_index], cmd) == 0)
        {
            return; // Don't add the command if it's the same as the last one
        }
       
    }
    // if (history.commands[history.count % MAX_HISTORY])
    // {
    //     free(history.commands[history.count % MAX_HISTORY]); // Free old command if it exists
    // }
    // else
    // {
    //     history.count++;
    // }
    // history.commands[history.count % MAX_HISTORY] = strdup(cmd); // Add new command
    if (history.commands[history.count % MAX_HISTORY])
    {
        free(history.commands[history.count % MAX_HISTORY]); // Free old command if it exists
    }
    history.commands[history.count % MAX_HISTORY] = strdup(cmd); // Add new command
    history.count++;                                             // Increment the count after adding the command

    save_history();

    // history.count++;
}

// void add_to_history(char* command) {
//     // List of valid commands
//     const char* valid_commands[] = {"echo", "pwd", "cd", "history", NULL};
//     int is_valid = 0;

//     // Check if the command is valid
//     for (int i = 0; valid_commands[i] != NULL; i++) {
//         if (strncmp(command, valid_commands[i], strlen(valid_commands[i])) == 0) {
//             is_valid = 1;
//             break;
//         }
//     }

//     // If the command is valid, add it to the history
//     if (is_valid) {
//         if (history.count < MAX_HISTORY) {
//             history[history_count] = strdup(command);  // Add to history
//             history_count++;
//         } else {
//             // If history is full, shift commands and add the new one at the end
//             free(history[0]);  // Free the first command
//             for (int i = 1; i < MAX_HISTORY; i++) {
//                 history[i - 1] = history[i];  // Shift commands
//             }
//             history[MAX_HISTORY - 1] = strdup(command);  // Add new command
//         }
//     }
// }
// Print the history (default 10 commands)
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
