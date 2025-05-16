#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 10000
#define MAX_WORDS 1000

// Function to compare two strings
int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}


int main() {
    // Read the input
    char text[MAX_CHARS];
    char c;
    while ((c = getchar()) != EOF) {
        text[strlen(text)] = c;
    }

    // Split the input into words
    char *words[MAX_WORDS];
    int word_count = 0;
    char *word = strtok(text, " \n\t");
    while (word != NULL) {
        words[word_count++] = word;
        word = strtok(NULL, " \n\t");
    }

    // Find longest word
    int longest_length = 0;
    for (int i = 0; i < word_count; i++) {
        int length = strlen(words[i]);
        if (length > longest_length) {
            longest_length = length;
        }
    }

    

    // Sort the words
    qsort(words, word_count, sizeof(char *), compare);

    // Remove duplicates and store unique words
    int unique_count = 0;
    char *unique_words[MAX_WORDS];
    for (int i = 0; i < word_count; i++) {
        if (i == 0 || strcmp(words[i], words[i - 1]) != 0) {
            unique_words[unique_count++] = words[i];
        }
    }

    // Print the unique words
    for (int i = 0; i < unique_count; i++) {
        if (i > 0) {
            printf(",");
        }
        printf("%s", unique_words[i]);
    }
    
    return 0;
}