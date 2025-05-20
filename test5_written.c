#include <stdio.h>
#include <stdlib.h>

// Define the character structure
typedef struct Character {
    int id;
    float hp;
    struct Character *next;
} Character;

// Function to create a new character node
Character* createCharacter(int id, float hp) {
    Character *newCharacter = (Character *)malloc(sizeof(Character));
    if (newCharacter == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newCharacter->id = id;
    newCharacter->hp = hp;
    newCharacter->next = NULL;
    return newCharacter;
}

// Function to add a character to the end of the list
void addCharacter(Character **head, int id, float hp) {
    Character *newCharacter = createCharacter(id, hp);
    
    // If the list is empty
    if (*head == NULL) {
        *head = newCharacter;
        return;
    }
    
    // Find the last node
    Character *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    // Add the new node at the end
    current->next = newCharacter;
}

// Function to apply damage to characters and remove those with HP <= 0
void applyDamage(Character **head, float *damages, int n) {
    Character *current = *head;
    Character *prev = NULL;
    int index = 0;
    
    while (current != NULL && index < n) {
        // Apply damage
        current->hp -= damages[index];
        
        // Check if character should be removed
        if (current->hp <= 0) {
            // If it's the head node
            if (prev == NULL) {
                *head = current->next;
                free(current);
                current = *head;
            } else {
                // If it's not the head node
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } else {
            // Move to next character
            prev = current;
            current = current->next;
        }
        
        index++;
    }
}

// Function to print the list of characters
void printCharacters(Character *head) {
    Character *current = head;
    while (current != NULL) {
        printf("%d %.2f\n", current->id, current->hp);
        current = current->next;
    }
}

// Function to free the list memory
void freeList(Character *head) {
    Character *current = head;
    Character *next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    int n, id;
    float hp;
    Character *head = NULL;
    
    // Read the number of characters
    scanf("%d", &n);
    
    // Read character data and build the linked list
    for (int i = 0; i < n; i++) {
        scanf("%d %f", &id, &hp);
        addCharacter(&head, id, hp);
    }
    
    // Allocate memory for damages array
    float *damages = (float *)malloc(n * sizeof(float));
    if (damages == NULL) {
        printf("Memory allocation failed\n");
        freeList(head);
        return 1;
    }
    
    // Read damage values
    for (int i = 0; i < n; i++) {
        scanf("%f", &damages[i]);
    }
    
    // Apply damage to characters
    applyDamage(&head, damages, n);
    
    // Print remaining characters
    printCharacters(head);
    
    // Free allocated memory
    freeList(head);
    free(damages);
    
    return 0;
}