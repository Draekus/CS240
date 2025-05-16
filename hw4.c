#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024
#define MAX_STRING_LENGTH 1001  
#define MAX_LINES_PER_FILE 100

// Structure to store a file's content
typedef struct {
    char *path;
    char **strings;
    int string_count;
} File;

// Function to read a file and store its content
File* read_file(const char *path) {
    // Allocate memory for the file structure
    File *file = (File*)malloc(sizeof(File));
    FILE *fp = fopen(path, "r");
    
    // Check if file opened successfully
    // If not, clean up and return NULL
    if (fp == NULL || file == NULL) {
        if (file != NULL) free(file);
        if (fp != NULL) fclose(fp);
        return NULL;
    }
    
    // Allocate memory for the path and copy it
    file->path = (char*)malloc(strlen(path) + 1);
    // Check if path allocation was successful
    // If not, clean up and return NULL
    if (file->path == NULL) {
        free(file);
        fclose(fp);
        return NULL;
    }
    
    // Populate file path
    strcpy(file->path, path);
    
    // Initialize string count and allocate memory for strings
    file->string_count = 0;
    file->strings = (char**)malloc(MAX_LINES_PER_FILE * sizeof(char*));
    // Check if strings allocation was successful
    // If not, clean up and return NULL
    if (file->strings == NULL) {
        free(file->path);
        free(file);
        fclose(fp);
        return NULL;
    }
    
    // Create a buffer to read lines
    char *buffer = (char*)malloc(MAX_STRING_LENGTH * sizeof(char));
    // Check if buffer allocation was successful
    // If not, clean up and return NULL
    if (buffer == NULL) {
        free(file->strings);
        free(file->path);
        free(file);
        fclose(fp);
        return NULL;
    }
    
    // Read lines from the file
    while (fgets(buffer, MAX_STRING_LENGTH, fp) && file->string_count < MAX_LINES_PER_FILE) {
        // Remove newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && *(buffer + len - 1) == '\n') {
            *(buffer + len - 1) = '\0';
            len--;
        }
        
        *(file->strings + file->string_count) = (char*)malloc(len + 1);
        // Check if memory allocation was successful
        // If not, clean up and return NULL
        if (*(file->strings + file->string_count) == NULL) {
            // Clean up previously allocated memory
            for (int i = 0; i < file->string_count; i++) {
                free(*(file->strings + i));
            }
            free(file->strings);
            free(file->path);
            free(file);
            free(buffer);
            fclose(fp);
            return NULL;
        }
        
        strcpy(*(file->strings + file->string_count), buffer);
        file->string_count++;
    }
    
    free(buffer);
    fclose(fp);
    return file;
}

// Function to free memory allocated for a file
void free_file(File *file) {
    // Check if file is NULL
    // If file is NULL, return
    if (file == NULL) return;
    
    // If file is not NULL, free the memory allocated for strings and path
    // Free the file structure itself
    for (int i = 0; i < file->string_count; i++) {
        free(*(file->strings + i));
    }
    free(file->strings);
    free(file->path);  
    free(file);
}

// Function to print file content separated by commas
void print_file(File *file) {
    // Check if file is NULL or has no strings
    // If file is NULL or has no strings, return
    if (file == NULL || file->string_count == 0) return;
    
    for (int i = 0; i < file->string_count; i++) {
        printf("%s", *(file->strings + i));
        if (i < file->string_count - 1) {
            printf(",");
        }
    }
    printf("\n");
}

// Function to print all files content
void print_all_files(File **files, int file_count) {
    // Check if files is NULL or file_count is 0
    // If files is NULL or file_count is 0, return
    if (files == NULL || file_count == 0) return;
    
    // Print each file's content
    // If file is NULL or has no strings, print newline
    // Otherwise, print file content
    for (int i = 0; i < file_count; i++) {
        if (((*(files + i))->string_count) == 0) {
            printf("\n");
        } 
        else { 
            print_file(*(files + i));
        }
        
    }
}

// Function to find and print the longest string in a file
void print_longest_string(File *file) {
    if (file == NULL || file->string_count == 0) return;
    
    int longest_idx = 0;
    size_t max_len = strlen(*(file->strings + 0));
    
    int i;
    for (i = 1; i < file->string_count; i++) {
        size_t len = strlen(*(file->strings + i));
        if (len > max_len) {
            max_len = len;
            longest_idx = i;
        }
    }
    
    printf("%s\n", *(file->strings + longest_idx));
}

// Function to find and print the file with the most strings
void print_longest_file(File **files, int file_count) {
    if (files == NULL || file_count == 0) return;
    
    int longest_idx = 0;
    int max_strings = (*(files + 0))->string_count;
    
    int i;
    for (i = 1; i < file_count; i++) {
        if ((*(files + i))->string_count > max_strings) {
            max_strings = (*(files + i))->string_count;
            longest_idx = i;
        }
    }
    
    printf("%s\n", (*(files + longest_idx))->path);
}

// Function to search for a string in all files and print the first file path containing it
void search_string(File **files, int file_count, const char *search_str) {
    if (files == NULL || file_count == 0 || search_str == NULL) return;

    
    // Search for the string in each file
    for (int i = 0; i < file_count; i++) {
        File *file = *(files + i);
        for (int j = 0; j < file->string_count; j++) {
            if (strcmp(*(file->strings + j), search_str) == 0) {
                printf("%s\n", file->path);
                return;
            }
        }
    }
}

// Comparison function for qsort to compare strings
int compare_strings(const void *a, const void *b) {
    // Cast void pointers to char pointer pointers (char **)
     const char *str1 = *(const char **)a;
     const char *str2 = *(const char **)b;
    
    // Compare strings and return the result
    return strcmp(str1, str2);
}

// Function to sort strings in a file (ascending ASCII order) using qsort
void sort_file(File *file) {
    if (file == NULL || file->string_count <= 1) return;
    
    // Use qsort to sort the strings
    qsort(file->strings, file->string_count, sizeof(char *), compare_strings);
}

// Function to remove all occurrences of a string from all files
void remove_string(File **files, int file_count, const char *remove_str) {
    // Check if files is NULL, file_count is 0, or remove_str is NULL
    // If files is NULL, file_count is 0, or remove_str is NULL, return
    if (files == NULL || file_count == 0 || remove_str == NULL) return;
    
    // Iterate through each file and remove the specified string
    // from the strings array
    int i, j;
    for (i = 0; i < file_count; i++) {
        File *file = *(files + i);
        j = 0;
        while (j < file->string_count) {
            if (strcmp(*(file->strings + j), remove_str) == 0) {
                // Remove this string by shifting all subsequent strings
                free(*(file->strings + j));
                int k;
                for (k = j; k < file->string_count - 1; k++) {
                    *(file->strings + k) = *(file->strings + k + 1);
                }
                file->string_count--;
            } else {
                j++;
            }
        }
    }
}

// Function to append one file's content to another
void append_file(File *dest, File *src) {
    // Check if destination or source file is NULL
    // If destination or source file is NULL, return
    if (dest == NULL || src == NULL) return;
    
    // Check if we need to resize the destination file's string array
    int new_count = dest->string_count + src->string_count;
    if (new_count > MAX_LINES_PER_FILE) {
        new_count = MAX_LINES_PER_FILE;
    }
    
    char **new_strings = (char**)realloc(dest->strings, new_count * sizeof(char*));
    if (new_strings == NULL) return;
    
    dest->strings = new_strings;
    
    // Copy strings from source to destination
    for (int i = 0; i < src->string_count && dest->string_count < MAX_LINES_PER_FILE; i++) {
        *(dest->strings + dest->string_count) = (char*)malloc(strlen(*(src->strings + i)) + 1);
        if (*(dest->strings + dest->string_count) == NULL) return;
        
        strcpy(*(dest->strings + dest->string_count), *(src->strings + i));
        dest->string_count++;
    }
}

// Function to execute commands from a command file
void execute_commands(const char *command_path, File **files, int file_count) {
    // Open the command file
    FILE *fp = fopen(command_path, "r");
    // Check if file opened successfully
    // If not, print error message and return
    if (fp == NULL) {
        printf("Error opening command file: %s\n", command_path);
        return;
    }
    
    // Allocate memory for the command buffer
    char *buffer = (char*)malloc(MAX_STRING_LENGTH * sizeof(char));
    // Check if buffer allocation was successful
    // If not, clean up and return
    if (buffer == NULL) {
        fclose(fp);
        return;
    }
    
    // Read commands from the command file
    // Process each command until EOF
    // or until the buffer is full
    while (fgets(buffer, MAX_STRING_LENGTH, fp)) {
        // Remove newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && *(buffer + len - 1) == '\n') {
            *(buffer + len - 1) = '\0';
        }

        // Initialize indices for file operations
        int idx1, idx2;
        
        /*      Parse commands      */
        // Print file content
        if (sscanf(buffer, "PRINT %d", &idx1) == 1) {
            if (idx1 >= 0 && idx1 < file_count) {
                print_file(*(files + idx1));
            }
        // Print all files content
        } else if (strcmp(buffer, "PRINT_ALL") == 0) {
            print_all_files(files, file_count);
        // Print longest string in a file
        } else if (sscanf(buffer, "PRINT_LONGEST %d", &idx1) == 1) {
            if (idx1 >= 0 && idx1 < file_count) {
                print_longest_string(*(files + idx1));
            }
        // Print longest file
        } else if (strcmp(buffer, "PRINT_LONGEST_FILE") == 0) {
            print_longest_file(files, file_count);
        // Search for the first ocurrence of a string in all files
        } else if (strncmp(buffer, "SEARCH ", 7) == 0) {
            // Extract search string starting from position 7 (after "SEARCH ")
            char *search_str = buffer + 7;
            if (strlen(search_str) > 0) {
                search_string(files, file_count, search_str);
            }
        // Sort a file's strings in ascending ASCII order
        } else if (sscanf(buffer, "SORT %d", &idx1) == 1) {
            if (idx1 >= 0 && idx1 < file_count) {
                sort_file(*(files + idx1));
            }
        // Remove all occurrences of a string from all files
        } else if (strncmp(buffer, "REMOVE ", 7) == 0) {
            // Extract remove string starting from position 7 (after "REMOVE ")
            char *remove_str = buffer + 7;
            if (strlen(remove_str) > 0) {
                remove_string(files, file_count, remove_str);
            }
        // Append one file's content to another
        } else if (sscanf(buffer, "APPEND %d %d", &idx1, &idx2) == 2) {
            if (idx1 >= 0 && idx1 < file_count && idx2 >= 0 && idx2 < file_count) {
                append_file(*(files + idx1), *(files + idx2));
            }
        }
    }
    
    // Clean up allocated memory
    free(buffer);
    fclose(fp);
}

int main() {
    int n;
    if(scanf("%d", &n) != 1) {
        printf("Wrong number of arguments \nEnter a single integer representing the number of files to be processed.\n");
        return 1;
    }
    
    // Skip the newline character after n
    getchar();
    
    // Allocate memory for file pointers
    File **files = (File**)malloc(n * sizeof(File*));
    // Check if memory allocation was successful
    // If not, print error message and return
    if (files == NULL) {
        printf("Memory allocation for File array failed.\n");
        return 1;
    }

    // Allocate memory for the file path
    char *path = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));
    // Check if memory allocation was successful
    // If not, clean up and return
    if (path == NULL) {
        printf("Memory allocation for File path failed.\n");
        free(files);
        return 1;
    }
    
    // Read file paths
    for (int i = 0; i < n; i++) {
        // Read file paths from stdin
        // Check if fgets was successful
        // If not, print error message and clean up
        if (fgets(path, MAX_PATH_LENGTH, stdin) == NULL) {
            printf("Error reading File path.\n");
            
            // Clean up allocated memory
            int j;
            for (j = 0; j < i; j++) {
                free_file(*(files + j));
            }
            free(files);
            free(path);
            return 1;
        }
        
        // Remove newline character if present
        size_t len = strlen(path);
        if (len > 0 && *(path + len - 1) == '\n') {
            // Replace newline character with null terminator
            *(path + len - 1) = '\0';
        }
        
        // Read the file and store its content
        *(files + i) = read_file(path);
        // Check if file reading was successful
        // If not, print error message and clean up
        if (*(files + i) == NULL) {
            printf("Error reading File: %s\n", path);
            
            // Clean up allocated memory
            int j;
            for (j = 0; j < i; j++) {
                free_file(*(files + j));
            }
            free(files);
            free(path);
            return 1;
        }
    }
    
    // Read the command file path
    // Check if fgets was successful
    // If not, print error message and clean up
    if (fgets(path, MAX_PATH_LENGTH, stdin) == NULL) {
        printf("Error reading command File path.\n");
        
        // Clean up allocated memory
        for (int i = 0; i < n; i++) {
            free_file(*(files + i));
        }
        free(files);
        free(path);
        return 1;
    }
    
    // Remove newline character if present
    size_t len = strlen(path);
    if (len > 0 && *(path + len - 1) == '\n') {
        // Replace newline character with null terminator
        *(path + len - 1) = '\0';
    }
    
    // Execute commands
    execute_commands(path, files, n);
    
    // Clean up allocated memory
    for (int i = 0; i < n; i++) {
        free_file(*(files + i));
    }
    free(files);
    free(path);
    
    return 0;
}