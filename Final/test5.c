#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the character structure
typedef struct Character {
    int id;
    float hp;
    float atk;
    struct Character *next;
} Character;

// Function to create a new character node
Character* createCharacter(int id, float hp, float atk) {
    Character *newCharacter = (Character *)malloc(sizeof(Character));
    newCharacter->id = id;
    newCharacter->hp = hp;
    newCharacter->atk = atk;
    newCharacter->next = NULL;
    return newCharacter;
}

// Function to add a character to the end of the list
void addCharacter(Character **head, int id, float hp, float atk) {
    Character *newCharacter = createCharacter(id, hp, atk);
    
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

// Function to find a character by ID
Character* findCharacter(Character *head, int id) {
    Character *current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to find a character and its previous character by ID
void findCharacterWithPrev(Character *head, int id, Character **character, Character **prev) {
    *prev = NULL;
    *character = head;
    
    while (*character != NULL && (*character)->id != id) {
        *prev = *character;
        *character = (*character)->next;
    }
}

// Function to swap two characters in a linked list by ID
void swapCharacters(Character **head, int id1, int id2) {
    // If IDs are the same, no swap needed
    if (id1 == id2) {
        return;
    }
    
    // Find characters and their previous nodes
    Character *prev1 = NULL, *curr1 = NULL;
    Character *prev2 = NULL, *curr2 = NULL;
    
    findCharacterWithPrev(*head, id1, &curr1, &prev1);
    findCharacterWithPrev(*head, id2, &curr2, &prev2);
    
    // If either character doesn't exist
    if (curr1 == NULL || curr2 == NULL) {
        return;
    }
    
    // Update previous nodes' next pointers
    if (prev1 != NULL) {
        prev1->next = curr2;
    } else {
        // curr1 is head
        *head = curr2;
    }
    
    if (prev2 != NULL) {
        prev2->next = curr1;
    } else {
        // curr2 is head
        *head = curr1;
    }
    
    // Swap next pointers between curr1 and curr2
    Character *temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;
    
    // Special case: if curr1 and curr2 are adjacent
    if (curr1->next == curr1) {
        curr1->next = curr2;
    } else if (curr2->next == curr2) {
        curr2->next = curr1;
    }
}

// Function to increase a character's HP by the given amount
void increaseHealth(Character *head, int id, float hpIncrease) {
    Character *character = findCharacter(head, id);
    if (character != NULL) {
        character->hp += hpIncrease;
    }
}

// Function to increase a character's ATK by the given amount
void increaseAttack(Character *head, int id, float atkIncrease) {
    Character *character = findCharacter(head, id);
    if (character != NULL) {
        character->atk += atkIncrease;
    }
}

// Function to remove a character from the list
void removeCharacter(Character **head, Character *prev, Character *current) {
    if (prev == NULL) {
        // If it's the head node
        *head = current->next;
    } else {
        // If it's not the head node
        prev->next = current->next;
    }
    free(current);
}

// Function to calculate total HP of a group
float calculateTotalHP(Character *head) {
    float total = 0.0;
    Character *current = head;
    while (current != NULL) {
        total += current->hp;
        current = current->next;
    }
    return total;
}

// Function to print a group of characters
void printGroup(Character *head) {
    Character *current = head;
    while (current != NULL) {
        printf("%d %.2f %.2f\n", current->id, current->hp, current->atk);
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

// Function to simulate one group attacking another
// Returns 1 if the defending group becomes empty, 0 otherwise
int attackGroup(Character **attackerGroup, Character **defenderGroup) {
    Character *attacker = *attackerGroup;
    Character *defender = *defenderGroup;
    Character *prevDefender = NULL;

    while (attacker != NULL && defender != NULL) {
        defender->hp -= attacker->atk;

        Character *nextDefender = defender->next;
        Character *nextAttacker = attacker->next;

        // Check if defender is dead
        if (defender->hp <= 0) {
            removeCharacter(defenderGroup, prevDefender, defender);
            defender = nextDefender;

            // Check if defending group is empty
            if (*defenderGroup == NULL) {
                return 1;
            }
        } else {
            prevDefender = defender;
            defender = nextDefender;
        }

        attacker = nextAttacker;
    }
    return 0;
}

// Function to simulate a battle round between two groups
int battleRound(Character **groupA, Character **groupB) {
    if (attackGroup(groupA, groupB)) {
        return 1; // Group A wins
    }
    if (attackGroup(groupB, groupA)) {
        return 2; // Group B wins
    }
    return 0; // No group is empty yet
}

int main() {
    Character *groupA = NULL;
    Character *groupB = NULL;
    int n, m, id;
    float hp, atk;
    char *command = (char *)malloc(20 * sizeof(char));
    
    // Read Group A
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %f %f", &id, &hp, &atk);
        addCharacter(&groupA, id, hp, atk);
    }
    
    // Read Group B
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %f %f", &id, &hp, &atk);
        addCharacter(&groupB, id, hp, atk);
    }
    
    // Process commands
    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "SWAP") == 0) {
            char *group = (char *)malloc(2 * sizeof(char));
            int id1, id2;
            scanf("%s %d %d", group, &id1, &id2);
            
            if (strcmp(group, "A") == 0) {
                swapCharacters(&groupA, id1, id2);
            } else if (strcmp(group, "B") == 0) {
                swapCharacters(&groupB, id1, id2);
            }
        } else if (strcmp(command, "HEALTH") == 0) {
             char *group = (char *)malloc(2 * sizeof(char));
            int id;
            float hpIncrease;
            scanf("%s %d %f", group, &id, &hpIncrease);
            
            if (strcmp(group, "A") == 0) {
                increaseHealth(groupA, id, hpIncrease);
            } else if (strcmp(group, "B") == 0) {
                increaseHealth(groupB, id, hpIncrease);
            }
        } else if (strcmp(command, "BUFF") == 0) {
             char *group = (char *)malloc(2 * sizeof(char));
            int id;
            float atkIncrease;
            scanf("%s %d %f", group, &id, &atkIncrease);
            
            if (strcmp(group, "A") == 0) {
                increaseAttack(groupA, id, atkIncrease);
            } else if (strcmp(group, "B") == 0) {
                increaseAttack(groupB, id, atkIncrease);
            }
        } else if (strcmp(command, "BATTLE_START") == 0) {
            int result = battleRound(&groupA, &groupB);
            
            // Check if either group is empty
            if (result == 1 || result == 2) {
                break;
            }
        }
    }
    
    // Print the group with higher total HP or Group A if they're equal
    float totalHpA = calculateTotalHP(groupA);
    float totalHpB = calculateTotalHP(groupB);
    
    if (totalHpA >= totalHpB) {
        printGroup(groupA);
    } else {
        printGroup(groupB);
    }
    
    // Free memory
    freeList(groupA);
    freeList(groupB);
    
    return 0;
}
