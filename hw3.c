#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 1000
#define MAX_N 1000000000

// Function to print all strings
void print_all(char **strings, int count) {
    if (count == 0) {
        printf("\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("%s", *(strings + i));
        if (i < count - 1) {
            printf(",");
        }
    }
    printf("\n");
}

// Function to print string at a given index
void print_index(char **strings, int idx, int count) {
    if (idx >= 0 && idx < count) {
        printf("%s\n", *(strings + idx));
    }
}

// Function to find and print the longest string
void print_longest(char **strings, int count) {
    if (count == 0) return;
    char *longest = *strings;
    for (int i = 1; i < count; i++) {
        if (strlen(*(strings + i)) > strlen(longest)) {
            longest = *(strings + i);
        }
    }
    printf("%s\n", longest);
}

// Function to swap two strings
void swap_strings(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort strings in ascending ASCII order
void sort_asc(char **strings, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(*(strings + i), *(strings + j)) > 0) {
                swap_strings(strings + i, strings + j);
            }
        }
    }
}

// Function to sort strings in descending ASCII order
void sort_dsc(char **strings, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(*(strings + i), *(strings + j)) < 0) {
                swap_strings(strings + i, strings + j);
            }
        }
    }
}

// Function to remove occurrences of a string
void remove_string(char **strings, int *count, char *target) {
    int i, j;
    for (i = 0, j = 0; i < *count; i++) {
        if (strcmp(*(strings + i), target) != 0) {
            *(strings + j) = *(strings + i);
            j++;
        }
    }
    *count = j;
}

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // Consume newline character

    char **strings = (char **)malloc(n * sizeof(char *));
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
            print_all(strings, count);
        } else if (strncmp(buffer, "PRINT ", 6) == 0) {
            int idx;
            if (sscanf(buffer + 6, "%d", &idx) == 1) {
                print_index(strings, idx, count);
            }
        } else if (strcmp(buffer, "PRINT_LONGEST") == 0) {
            print_longest(strings, count);
        } else if (strcmp(buffer, "SORT ASC") == 0) {
            sort_asc(strings, count);
        } else if (strcmp(buffer, "SORT DSC") == 0) {
            sort_dsc(strings, count);
        } else if (strncmp(buffer, "SWAP ", 5) == 0) {
            int idx1, idx2;
            if (sscanf(buffer + 5, "%d %d", &idx1, &idx2) == 2) {
                if (idx1 >= 0 && idx1 < count && idx2 >= 0 && idx2 < count) {
                    swap_strings(strings + idx1, strings + idx2);
                }
            }
        } else if (strncmp(buffer, "REMOVE ", 7) == 0) {
            remove_string(strings, &count, buffer + 7);
        } else {
            printf("Unrecognized command: %s\n", buffer);
        }
    }

    // Free all the dynamically allocated memory
    for (int i = 0; i < count; i++) {
        free(*(strings + i));
    }
    free(strings);
    free(buffer); 

    return 0;
}
