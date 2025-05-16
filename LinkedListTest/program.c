#include <stdio.h>
#include <stdlib.h> // Required for malloc and free

// Structure to hold student data
typedef struct
{
    int id;
    float gpa;
} Student;

// Structure for the linked list node
// Using pointer notation explicitly for struct members
typedef struct Node
{
    Student data;
    struct Node *next;
} Node;

// --- Function Prototypes ---

// Creates a new node
Node *createNode(int id, float gpa);

// Adds a new node to the head of the list
Node *addHead(Node **head_ref, int id, float gpa);

// Adds a new node to the end of the list
Node *addLast(Node **head_ref, int id, float gpa);

// Replaces the head of the list with a new node
Node *replaceHead(Node **head_ref, int id, float gpa);

// Replace a node in the list
Node *replaceNode(Node **head_ref, int id, float gpa);

// Sort the list in ascending order based on GPA
Node *sortList(Node **head_ref);

// Sort the list in descending order based on GPA
Node *sortListDesc(Node **head_ref);

// Reverse the list
Node *reverseList(Node **head_ref);

// Merge two lists
Node *mergeLists(Node **head_ref1, Node **head_ref2);

// Merge two lists in descending order
Node *mergeListsDesc(Node **head_ref1, Node **head_ref2);

// Merge two lists in ascending order
Node *mergeListsAsc(Node **head_ref1, Node **head_ref2);

// Prints the list in reverse order recursively
void printReverse(Node *node);

// Prints the list in ascending order
void printAscending(Node *node);

// Prints the list in descending order
void printDescending(Node *node);

// Print the list
void printList(Node *node);

// Frees the memory used by the list
void freeList(Node **head_ref);

// --- Main Function ---
int main()
{
    Node *head = NULL; // Head of the linked list, initially empty
    int id;
    float gpa;

    // 1. Read student data from standard input until EOF or invalid input
    // scanf returns the number of items successfully read.
    // We expect 2 items (id and gpa) per line.
    // The loop continues as long as scanf successfully reads 2 items.
    printf("Enter student data (ID GPA) per line. Press Ctrl+D (Linux/macOS) or Ctrl+Z then Enter (Windows) to stop:\n");
    while (scanf("%d %f", &id, &gpa) == 2)
    {
        // Add the read student data to the end of the list
        addLast(&head, id, gpa);
    }

    // 2. Print the linked list in reverse order
    printf("\nStudent list in reverse order:\n");
    printReverse(head);

    // 3. Clean up allocated memory
    freeList(&head);

    return 0; // Indicate successful execution
}

// --- Function Implementations ---

// Creates a new node
Node *createNode(int id, float gpa)
{
    // Allocate memory for the new node using malloc
    Node *newNode = (Node *)malloc(sizeof(Node));
    // Check if memory allocation was successful
    if (newNode == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed for new node.\n");
        // Exit the program if memory cannot be allocated
        exit(1);
    }
    // Assign data using explicit pointer dereferencing
    (*(newNode)).data.id = id;
    (*(newNode)).data.gpa = gpa;
    // Initialize the next pointer to NULL
    (*(newNode)).next = NULL;
    return newNode; // Return the pointer to the newly created node
}

// Adds a new node to the head of the list
// Takes a pointer to the head pointer (Node **) to modify the head
Node *addHead(Node **head_ref, int id, float gpa)
{
    // Create a new node with the given data
    Node *newNode = createNode(id, gpa);

    // Case 1: If the list is empty, the new node becomes the head
    if (*head_ref == NULL)
    {
        *head_ref = newNode;
        return newNode; // Node added, function finished
    }

    // Case 2: The list is not empty, link the new node to the current head
    (*(newNode)).next = *head_ref;

    // Update the head pointer to point to the new node
    *head_ref = newNode;

    return newNode; // Return the new head of the list
}

// Adds a new node to the end of the list
// Takes a pointer to the head pointer (Node **) to modify the head
Node *addLast(Node **head_ref, int id, float gpa)
{
    // Create a new node with the given data
    Node *newNode = createNode(id, gpa);

    // Case 1: If the list is empty, the new node becomes the head
    if (*head_ref == NULL)
    {
        *head_ref = newNode;
        return; // Node added, function finished
    }

    // Case 2: The list is not empty, find the last node
    Node *current = *head_ref;
    while (current->next != NULL)
    {
        current = current->next;
    }

    // Link the new node to the end of the list
    current->next = newNode;

    return *head_ref; // Return the head of the list
}

// Replaces the head of the list with a new node
// Takes a pointer to the head pointer (Node **) to modify the head
Node *replaceHead(Node **head_ref, int id, float gpa)
{
    // Create a new node with the given data
    Node *newNode = createNode(id, gpa);

    // Case 1: If the list is empty, the new node becomes the head
    if (*head_ref == NULL)
    {
        *head_ref = newNode;
        return newNode; // Node added, function finished
    }

    // Case 2: The list is not empty, link the new node to the current head
    (*(newNode)).next = *head_ref;

    // Update the head pointer to point to the new node
    *head_ref = newNode;

    return newNode; // Return the new head of the list
}

// Replaces a node in the list
// Takes a pointer to the head pointer (Node **) to modify the head
Node *replaceNode(Node **head_ref, int id, float gpa)
{
    // Create a new node with the given data
    Node *newNode = createNode(id, gpa);

    // Case 1: If the list is empty, the new node becomes the head
    if (*head_ref == NULL)
    {
        *head_ref = newNode;
        return newNode; // Node added, function finished
    }

    // Case 2: The list is not empty, link the new node to the current head
    (*(newNode)).next = *head_ref;

    // Update the head pointer to point to the new node
    *head_ref = newNode;

    return newNode; // Return the new head of the list
}

// Sorts the list in ascending order based on GPA
// Takes a pointer to the head pointer (Node **) to modify the head 
Node *sortList(Node **head_ref)
{
    // Base case: if the list is empty or has only one node, return the head
    if (*head_ref == NULL || (*head_ref)->next == NULL)
        return *head_ref;

    // Pointer to the current node
    Node *current = *head_ref;
    Node *nextNode = NULL;

    // Traverse the list and sort it in ascending order based on GPA
    while (current != NULL)
    {
        nextNode = current->next;
        while (nextNode != NULL)
        {
            if (current->data.gpa > nextNode->data.gpa)
            {
                // Swap the data of the two nodes
                Student temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }

    return *head_ref; // Return the head of the sorted list
}

// Sorts the list in descending order based on GPA
// Takes a pointer to the head pointer (Node **) to modify the head
Node *sortListDesc(Node **head_ref)
{
    // Base case: if the list is empty or has only one node, return the head
    if (*head_ref == NULL || (*head_ref)->next == NULL)
        return *head_ref;

    // Pointer to the current node
    Node *current = *head_ref;
    Node *nextNode = NULL;

    // Traverse the list and sort it in descending order based on GPA
    while (current != NULL)
    {
        nextNode = current->next;
        while (nextNode != NULL)
        {
            if (current->data.gpa < nextNode->data.gpa)
            {
                // Swap the data of the two nodes
                Student temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }

    return *head_ref; // Return the head of the sorted list
}

// Merges two lists in descending order
// Takes pointers to the head pointers of the two lists (Node **)
Node *mergeListsDesc(Node **head_ref1, Node **head_ref2)
{
    // If either list is empty, return the other list
    if (*head_ref1 == NULL)
        return *head_ref2;
    if (*head_ref2 == NULL)
        return *head_ref1;

    // Create a new node to hold the merged list
    Node *mergedHead = NULL;

    // Compare the first nodes of both lists and choose the larger one
    if ((*head_ref1)->data.gpa >= (*head_ref2)->data.gpa)
    {
        mergedHead = *head_ref1; // Point to the first list's head
        *head_ref1 = (*head_ref1)->next; // Move to the next node in the first list
    }
    else
    {
        mergedHead = *head_ref2; // Point to the second list's head
        *head_ref2 = (*head_ref2)->next; // Move to the next node in the second list
    }

    // Pointer to keep track of the last node in the merged list
    Node *current = mergedHead;

    // Merge the remaining nodes from both lists
    while (*head_ref1 != NULL && *head_ref2 != NULL)
    {
        if ((*head_ref1)->data.gpa >= (*head_ref2)->data.gpa)
        {
            current->next = *head_ref1; // Link to the larger node
            current = current->next;     // Move to last node in merged list
            *head_ref1 = (*head_ref1)->next; // Move to next node in first list
        }
        else
        {
            current->next = *head_ref2; // Link to the larger node
            current = current->next;     // Move to last node in merged list
            *head_ref2 = (*head_ref2)->next; // Move to next node in second list
        }
    }

    // If there are remaining nodes in either list, link them to the end of merged list
    if (*head_ref1 != NULL)
        current->next = *head_ref1;
    else
        current->next = *head_ref2;

    return mergedHead; // Return the head of the merged list
}

// Merges two lists in ascending order
// Takes pointers to the head pointers of the two lists (Node **)
Node *mergeListsAsc(Node **head_ref1, Node **head_ref2)
{
    // If either list is empty, return the other list
    if (*head_ref1 == NULL)
        return *head_ref2;
    if (*head_ref2 == NULL)
        return *head_ref1;

    // Create a new node to hold the merged list
    Node *mergedHead = NULL;

    // Compare the first nodes of both lists and choose the smaller one
    if ((*head_ref1)->data.gpa <= (*head_ref2)->data.gpa)
    {
        mergedHead = *head_ref1; // Point to the first list's head
        *head_ref1 = (*head_ref1)->next; // Move to the next node in the first list
    }
    else
    {
        mergedHead = *head_ref2; // Point to the second list's head
        *head_ref2 = (*head_ref2)->next; // Move to the next node in the second list
    }

    // Pointer to keep track of the last node in the merged list
    Node *current = mergedHead;

    // Merge the remaining nodes from both lists
    while (*head_ref1 != NULL && *head_ref2 != NULL)
    {
        if ((*head_ref1)->data.gpa <= (*head_ref2)->data.gpa)
        {
            current->next = *head_ref1; // Link to the smaller node
            current = current->next;     // Move to last node in merged list
            *head_ref1 = (*head_ref1)->next; // Move to next node in first list
        }
        else
        {
            current->next = *head_ref2; // Link to the smaller node
            current = current->next;     // Move to last node in merged list
            *head_ref2 = (*head_ref2)->next; // Move to next node in second list
        }
    }

    // If there are remaining nodes in either list, link them to the end of merged list
    if (*head_ref1 != NULL)
        current->next = *head_ref1;
    else
        current->next = *head_ref2;

    return mergedHead; // Return the head of the merged list
}



// Replaces the head of the list with a new node
// Takes a pointer to the head pointer (Node **) to modify the head
Node *replaceHead(Node **head_ref, int id, float gpa)
{
    // Create a new node with the given data
    Node *newNode = createNode(id, gpa);

    // Case 1: If the list is empty, the new node becomes the head
    if (*head_ref == NULL)
    {
        *head_ref = newNode;
        return newNode; // Node added, function finished
    }

    // Case 2: The list is not empty, link the new node to the current head
    (*(newNode)).next = *head_ref;

    // Update the head pointer to point to the new node
    *head_ref = newNode;

    return newNode; // Return the new head of the list
}

// Replace the tail of the list with a new node
// Takes a pointer to the head pointer (Node **) to modify the head
Node *replaceTail(Node **head_ref, int id, float gpa)
{
    // Create a new node with the given data
    Node *newNode = createNode(id, gpa);

    // Case 1: If the list is empty, the new node becomes the head
    if (*head_ref == NULL)
    {
        *head_ref = newNode;
        return newNode; // Node added, function finished
    }

    // Case 2: The list is not empty, find the last node
    Node *current = *head_ref;
    while (current->next != NULL)
    {
        current = current->next;
    }

    // Link the new node to the end of the list
    current->next = newNode;

    return *head_ref; // Return the head of the list
// Reverses the linked list recursively
// Takes a pointer to the head pointer (Node **) to modify the head
Node *reverseList(Node **head_ref)
{
    // Base case: if the list is empty or has only one node, return the head
    if (*head_ref == NULL || (*head_ref)->next == NULL)
        return *head_ref;

    // rest points to the second node in the list
    Node *rest = (*head_ref)->next;

    // Recursively reverse the rest of the list; new_head will be the new head after reversal
    Node *new_head = reverseList(&rest);

    // Make the next node's next pointer point back to the current node (reverse the link)
    (*head_ref)->next->next = *head_ref;

    // Set the current node's next pointer to NULL (it will become the last node)
    (*head_ref)->next = NULL;

    // Update the head_ref to point to the new head of the reversed list
    *head_ref = new_head;

    // Return the new head pointer
    return *head_ref;
}

// Merges two lists
// Takes pointers to the head pointers of the two lists (Node **)
Node *mergeLists(Node **head_ref1, Node **head_ref2)
{
    // If either list is empty, return the other list
    if (*head_ref1 == NULL)
        return *head_ref2;
    if (*head_ref2 == NULL)
        return *head_ref1;

    // Create a new node to hold the merged list
    Node *mergedHead = NULL;

    // Compare the first nodes of both lists and choose the smaller one
    if ((*head_ref1)->data.gpa <= (*head_ref2)->data.gpa)
    {
        mergedHead = *head_ref1; // Point to the first list's head
        *head_ref1 = (*head_ref1)->next; // Move to the next node in the first list
    }
    else
    {
        mergedHead = *head_ref2; // Point to the second list's head
        *head_ref2 = (*head_ref2)->next; // Move to the next node in the second list
    }

    // Pointer to keep track of the last node in the merged list
    Node *current = mergedHead;

    // Merge the remaining nodes from both lists
    while (*head_ref1 != NULL && *head_ref2 != NULL)
    {
        if ((*head_ref1)->data.gpa <= (*head_ref2)->data.gpa)
        {
            current->next = *head_ref1; // Link to the smaller node
            current = current->next;     // Move to the last node in merged list
            *head_ref1 = (*head_ref1)->next; // Move to next node in first list
        }
        else
        {
            current->next = *head_ref2; // Link to the smaller node
            current = current->next;     // Move to last node in merged list
            *head_ref2 = (*head_ref2)->next; // Move to next node in second list
        }
    }

    // If there are remaining nodes in either list, link them to the end of merged list
    if (*head_ref1 != NULL)
        current->next = *head_ref1;
    else
        current->next = *head_ref2;

    return mergedHead; // Return the head of the merged list
}

// Prints the list in ascending order
// Takes a pointer to the head of the list (Node *)
void printAscending(Node *node)
{
    // Base Case: If the current node is NULL, we've reached the end
    // of the list (or the list was empty), so just return.
    if (node == NULL)
    {
        return;
    }

    // Action: Print the data of the current node
    printf("%d %.2f\n", (*(node)).data.id, (*(node)).data.gpa);

    // Recursive Step: Call printAscending for the next node
    printAscending((*(node)).next);
}


// Prints the list in ascending order
// Takes a pointer to the head of the list (Node *)
void printList(Node *node)
{
    // Base Case: If the current node is NULL, we've reached the end
    // of the list (or the list was empty), so just return.
    if (node == NULL)
    {
        return;
    }

    // Action: Print the data of the current node
    printf("%d %.2f\n", (*(node)).data.id, (*(node)).data.gpa);

    // Recursive Step: Call printList for the next node
    printList((*(node)).next);
}

// Prints the list in descending order
// Takes a pointer to the head of the list (Node *)
void printDescending(Node *node)
{
    // Base Case: If the current node is NULL, we've reached the end
    // of the list (or the list was empty), so just return.
    if (node == NULL)
    {
        return;
    }

    // Recursive Step: Call printDescending for the next node first.
    // This will cause the function calls to stack up until the end
    // of the list is reached.
    printDescending((*(node)).next);

    // Action: After the recursive call for the rest of the list returns,
    // print the data of the *current* node. This happens on the way
    // "back" from the recursion, resulting in reverse order printing.
    printf("%d %.2f\n", (*(node)).data.id, (*(node)).data.gpa);
}

// Prints the list in reverse order recursively
// Takes a pointer to the current node being considered
void printReverse(Node *node)
{
    // Base Case: If the current node is NULL, we've reached the end
    // of the list (or the list was empty), so just return.
    if (node == NULL)
    {
        return;
    }

    // Recursive Step: Call printReverse for the *next* node first.
    // This will cause the function calls to stack up until the end
    // of the list is reached.
    printReverse((*(node)).next);

    // Action: After the recursive call for the rest of the list returns,
    // print the data of the *current* node. This happens on the way
    // "back" from the recursion, resulting in reverse order printing.
    printf("%d %.2f\n", (*(node)).data.id, (*(node)).data.gpa);
}

// Frees the memory used by the list
// Takes a pointer to the head pointer (Node **) to set the head to NULL after freeing
void freeList(Node **head_ref)
{
    Node *current = *head_ref; // Start at the head
    Node *nextNode = NULL;     // Temporary pointer to store the next node

    // Iterate through the list
    while (current != NULL)
    {
        // Store the pointer to the next node before freeing the current one
        nextNode = (*(current)).next;
        // Free the memory allocated for the current node
        free(current);
        // Move to the next node
        current = nextNode;
    }

    // Set the original head pointer to NULL to indicate the list is now empty
    *head_ref = NULL;
}
