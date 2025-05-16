#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a student node
typedef struct StudentNode {
    int id;
    float gpa;
    struct StudentNode* next;
} StudentNode;

// Function to create a new student node
StudentNode* createNode(int id, float gpa) {
    StudentNode* newNode = (StudentNode*)malloc(sizeof(StudentNode));
    newNode->id = id;
    newNode->gpa = gpa;
    newNode->next = NULL;
    return newNode;
}

// Function to print all nodes in the linked list
void printAll(StudentNode* head) {
    StudentNode* current = head;
    while (current != NULL) {
        printf("%d %.2f\n", current->id, current->gpa);
        current = current->next;
    }
}

// Function to reverse the linked list
void reverse(StudentNode** head) {
    StudentNode* prev = NULL;
    StudentNode* current = *head;
    StudentNode* next = NULL;
    
    while (current != NULL) {
        // Store next
        next = current->next;
        
        // Reverse current node's pointer
        current->next = prev;
        
        // Move pointers one position ahead
        prev = current;
        current = next;
    }
    
    // Update head pointer
    *head = prev;
}

// Function to find a node by ID
StudentNode* findNodeById(StudentNode* head, int id) {
    StudentNode* current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to swap two nodes with given IDs
void swapNodes(StudentNode** head, int id1, int id2) {
    // Nothing to do if both IDs are the same
    if (id1 == id2) return;
    
    // Search for nodes with id1 and id2
    StudentNode* node1 = NULL;
    StudentNode* prev1 = NULL;
    StudentNode* node2 = NULL;
    StudentNode* prev2 = NULL;
    StudentNode* current = *head;
    StudentNode* prev = NULL;
    
    // Find nodes and their previous nodes
    while (current != NULL && (node1 == NULL || node2 == NULL)) {
        if (current->id == id1) {
            node1 = current;
            prev1 = prev;
        } else if (current->id == id2) {
            node2 = current;
            prev2 = prev;
        }
        prev = current;
        current = current->next;
    }
    
    // If either ID doesn't exist, do nothing
    if (node1 == NULL || node2 == NULL) {
        return;
    }
    
    // If prev1 is NULL, node1 is the head
    if (prev1 == NULL) {
        *head = node2;
    } else {
        prev1->next = node2;
    }
    
    // If prev2 is NULL, node2 is the head
    if (prev2 == NULL) {
        *head = node1;
    } else {
        prev2->next = node1;
    }
    
    // Swap next pointers
    StudentNode* temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;
    
    // Handle special case: nodes are adjacent
    if (node1->next == node1) {
        node1->next = node2;
    } else if (node2->next == node2) {
        node2->next = node1;
    }
}

// Function to free all the memory allocated for the linked list
void freeList(StudentNode* head) {
    StudentNode* current = head;
    StudentNode* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    char *inputFilePath = (char *)malloc(101 * sizeof(char));
    char *commandFilePath = (char *)malloc(101 * sizeof(char));
    FILE *inputFile, *commandFile;
    StudentNode* head = NULL;
    
    // Read the input file path
    if (fgets(inputFilePath, 101, stdin) == NULL) {
        printf("Error reading input file path.\n");
        return 1;
    }
    
    // Remove newline character if present
    char *newline = strchr(inputFilePath, '\n');
    if (newline) {
        *newline = '\0';
    }
    
    // Read the command file path
    if (fgets(commandFilePath, 101, stdin) == NULL) {
        printf("Error reading command file path.\n");
        return 1;
    }
    
    // Remove newline character if present
    char *ptr = strchr(commandFilePath, '\n');
    if (ptr) {
        *ptr = '\0';
    }
    
    // Open the input file
    inputFile = fopen(inputFilePath, "r");
    if (inputFile == NULL) {
        printf("Could not open input file: %s\n", inputFilePath);
        return 1;
    }
    
    // Read student data from input file and build linked list
    int id;
    float gpa;
    
    while (fscanf(inputFile, "%d %f", &id, &gpa) == 2) {
        if (head == NULL) {
            head = createNode(id, gpa);
        } else {
            StudentNode* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = createNode(id, gpa);
        }
    }
    
    fclose(inputFile);
    
    // Open the command file
    commandFile = fopen(commandFilePath, "r");
    if (commandFile == NULL) {
        printf("Could not open command file: %s\n", commandFilePath);
        freeList(head);
        return 1;
    }
    
    // Process commands
    char *command = (char *)malloc(20 * sizeof(char));
    while (fscanf(commandFile, "%s", command) == 1) {
        if (strcmp(command, "PRINT_ALL") == 0) {
            printAll(head);
        } else if (strcmp(command, "REVERSE") == 0) {
            reverse(&head);
        } else if (strcmp(command, "SWAP") == 0) {
            int id1, id2;
            if (fscanf(commandFile, "%d %d", &id1, &id2) == 2) {
                swapNodes(&head, id1, id2);
            }
        }
    }
    
    fclose(commandFile);
    
    // Free the linked list
    freeList(head);
    
    return 0;
}