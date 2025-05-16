#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() { 
    char str[1000];
    char c;
    int char_count = 0;
    // Read the input
    while ((c = getchar()) != EOF) {
        str[strlen(str)] = c;
        char_count++;
    }
    // Print the input in reverse order
    for (int i = char_count - 1; i >= 0; i--) {
        putchar(str[i]);
    }

    // Function to remove duplicate strings from char array
    char **strings = malloc(MAX_LINES * sizeof(char *));
    if (!strings) {
        return 1;
    }
    char **unique_strings = malloc(MAX_LINES * sizeof(char *));
    if (!unique_strings) {
        free(strings);
        return 1;
    }
    // Read strings
    int total_count = 0;
    int unique_count = 0;
    while (total_count < MAX_LINES) {
        // Allocate memory for current string
        *(strings + total_count) = malloc(MAX_STRING_LENGTH * sizeof(char));
        if (!(*(strings + total_count))) {
            // Free previously allocated memory
            char **cleanup = strings;
            while (cleanup < strings + total_count) {
                free(*cleanup);
                ++cleanup;
            }
            free(strings);
            free(unique_strings);
            return 1;
        }
        // Read input line
        if (fgets(*(strings + total_count), MAX_STRING_LENGTH, stdin) == NULL) {
            break; // End of input
        }
        // Remove trailing newline
        char *newline = *(strings + total_count);
        newline[strcspn(newline, "\n")] = '\0';
        ++total_count;
    }
    // Check for duplicates
    for (int i = 0; i < total_count; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strcmp(*(strings + i), *(unique_strings + j)) == 0) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            *(unique_strings + unique_count) = malloc(MAX_STRING_LENGTH * sizeof(char));
            if (!(*(unique_strings + unique_count))) {
                // Free previously allocated memory
                char **cleanup = strings;
                while (cleanup < strings + total_count + 1) {
                    free(*cleanup);
                    ++cleanup;
                }
                free(strings);
                free(unique_strings);
                return 1;
            }
            strcpy(*(unique_strings + unique_count), *(strings + i));
            unique_count++;
        }
    }
    return 0;
}