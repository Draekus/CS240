#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 1001

int is_duplicate(char **first_string, char **last_string, char *current_string) {
    char **check_string = first_string;
    
    while (check_string < last_string) {
        if (strcmp(*check_string, current_string) == 0) {
            return 1; // Duplicate found
        }
        ++check_string;
    }
    return 0; // No duplicate
}

int main() {
    int n;
    
    // Read number of strings
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    getchar(); // Consume newline
    
    // Allocate memory for array of string pointers
    char **strings = (char **)malloc(n * sizeof(char *));
    if (!strings) {
        return 1;
    }
    
    // Read strings
    char **current_string = strings;
    char **end_strings = strings + n;
    
    while (current_string < end_strings) {
        *current_string = malloc(MAX_STRING_LENGTH * sizeof(char));
        if (!*current_string) {
            // Free previously allocated memory
            char **cleanup = strings;
            while (cleanup < current_string) {
                free(*cleanup);
                ++cleanup;
            }
            free(strings);
            return 1;
        }
        
        
        // Remove trailing newlineR
        char *newline = *current_string;
        while (*newline) {
            if (*newline == '\n') {
                *newline = '\0';
                break;
            }
            ++newline;
        }
        
        ++current_string;
    }
    
    // Process commands
    char *buffer = NULL; // Use a dynamically allocated buffer
    size_t buffer_size = 0; // Size of the buffer
    int count = 0;

    for (int i = 0; i < n; i++) {
        size_t line_length = getline(&buffer, &buffer_size, stdin); // Read the entire line
        if (line_length == -1) {
            // Handle unexpected EOF
            break;
        }
        *(buffer + line_length - 1) = '\0'; // Remove the newline character
        *(strings + count) = strdup(buffer); // Duplicate the string
        count++;
    }

    while (getline(&buffer, &buffer_size, stdin) != -1) {
        // Remove the newline character
        *(buffer + strcspn(buffer, "\n")) = '\0'; 

        if (strcmp(buffer, "PRINT_ALL") == 0) {
            char **print_string = strings;
            while (print_string < strings + n) {
                printf("%s", *print_string);
                ++print_string;
                if (print_string < strings + n) {
                    printf(",");
                }
            }
            printf("\n");
        }
        else if (strcmp(buffer, "REMOVE_DUP") == 0) {
            char **write_ptr = strings;
            char **read_ptr = strings;
            char **end_ptr = strings + n;
            
            while (read_ptr < end_ptr) {
                // Check if current string is a duplicate
                if (!is_duplicate(strings, write_ptr, *read_ptr)) {
                    // If not a duplicate, move the string
                    if (write_ptr != read_ptr) {
                        *write_ptr = *read_ptr;
                    }
                    ++write_ptr;
                }
                else {
                    // Free duplicate string
                    free(*read_ptr);
                }
                ++read_ptr;
            }
            
            // Update n to new unique count
            n = write_ptr - strings;
        } 
    }
   
    
    // Free allocated memory
    char **cleanup = strings;
    while (cleanup < strings + n) {
        free(*cleanup);
        ++cleanup;
    }
    free(strings);
    
    return 0;
}