#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 100

struct Node
{
    char *word;
    struct Node *next;
} typedef Node;

Node *insert(Node *head, char *word)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->word = word;
    new_node->next = NULL;
    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        Node *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }

    return head;
}

Node *removeNode(Node *head, char c)
{
    if (head == NULL)
    {
        return head;
    }
    while (head != NULL && *(head->word + strlen(head->word) - 1) == c)
    {
        Node *temp = head;
        head = head->next;
        temp->next = NULL;
        free(temp);
    }

    if (head == NULL)
    {
        return head;
    }
    Node *current = head;

    while (current->next != NULL)
    {
        if (*(current->next->word + strlen(current->next->word) - 1) == c)
        {
            Node *temp = current->next;
            current->next = current->next->next;
            temp->next = NULL;
            free(temp);
        }
        else
        {
            current = current->next;
        }
    }
    return head;
}
// Insert a new node in the middle of the list
Node *insertMiddle(Node *head, char *word)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->word = word;
    new_node->next = NULL;
    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        Node *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }

    return head;
}
void printList(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%s", current->word);
        if (current->next != NULL)
        {
            printf(" ");
        }
        current = current->next;
    }
}
Node *reverseList(Node *head)
{
    Node *prev = NULL;
    Node *current = head;
    Node *next_node;
    while (current != NULL)
    {
        next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;
    }
    head = prev;
    return head;
}
int main()
{
    Node *head = NULL;
    char c;
    char *input = malloc(sizeof(char) * MAX_LENGTH);
    while (scanf("%s%c", input, &c) == 2)
    {
        head = insert(head, input);
        input = malloc(sizeof(char) * MAX_LENGTH);
    }
    c = *input;
    head = removeNode(head, c);
    head = reverseList(head);
    printList(head);
    free(head);
}