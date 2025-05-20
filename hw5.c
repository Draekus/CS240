#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define the structure for a student node
typedef struct Student {
    int id;
    float gpa;
    char *name;
    struct Student *next;
} Student;

// Function prototypes
Student *createStudent(int id, float gpa, char *name);
void addStudent(Student **head, Student *newStudent);
void printStudent(Student *student);
void printAll(Student *head);
Student *findStudent(Student *head, int id);
void printStudentById(Student *head, int id);
void removeStudent(Student **head, int id);
void printBelowGPA(Student *head, float gpa);
void printAboveGPA(Student *head, float gpa);
void sortByName(Student **head);
void sortByGPA(Student **head);
void freeList(Student **head);
char *trimWhiteSpace(char *str);

int main() {
    Student *head = NULL;
    int n, id;
    float gpa;
    char *buffer = malloc(1024 * sizeof(char));
    size_t buffer_size = 1024;
    char *first_name = malloc(1024 * sizeof(char));
    char *last_name = malloc(1024 * sizeof(char));
    if (!buffer || !first_name || !last_name || buffer_size <= 0) {
        fprintf(stderr, "Memory allocation of text buffers failed\n");
        free(buffer);
        free(first_name);
        return 1;
    }
    
    // Read the number of students
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error reading number of students\n");
        return 1;
    }
    
    // Consume the newline character
    getchar();
    
    // Read n students
    for (int i = 0; i < n; i++) {
        if (fgets(buffer, buffer_size, stdin) == NULL) {
            fprintf(stderr, "Error reading student data\n");
            freeList(&head);
            return 1;
        }
        
        // Parse student data
        if (sscanf(buffer, "%d %f %s %s", &id, &gpa, first_name, last_name) != 4) {
            fprintf(stderr, "Error parsing student data\n");
            freeList(&head);
            return 1;
        }
        // Concatenate first and last name using pointers
        char *name = malloc(strlen(first_name) + strlen(last_name) + 2);
        if (!name) {
            fprintf(stderr, "Memory allocation for name failed\n");
            freeList(&head);
            return 1;
        }
        strcpy(name, first_name);
        strcat(name, " ");
        strcat(name, last_name);
        // Trim trailing whitespace from name
        char *trimmedName = trimWhiteSpace(name);
        
        // Create and add new student to the list
        Student *newStudent = createStudent(id, gpa, trimmedName);
        if (!newStudent) {
            fprintf(stderr, "Memory allocation for newStudent() failed\n");
            freeList(&head);
            return 1;
        }
        
        addStudent(&head, newStudent);
    }
    
    // Process commands
    while (getline(&buffer, &buffer_size, stdin) != -1) {
        // Remove the newline character
        *(buffer + strcspn(buffer, "\n")) = '\0'; 
        if (strcmp(buffer, "PRINT_ALL") == 0) {
            printAll(head);
        } else if (strncmp(buffer, "PRINT ", 6) == 0) {
            if (sscanf(buffer + 6, "%d", &id) == 1) {
                printStudentById(head, id);
            }
        } else if (strncmp(buffer, "ADD ", 4) == 0) {
            char *ptr = buffer + 4;
            if (sscanf(ptr, "%d %f %s %s", &id, &gpa, first_name, last_name) == 4) {
                // Concatenate first and last name using pointers
                char *name = malloc(strlen(first_name) + strlen(last_name) + 2);
                if (!name) {
                fprintf(stderr, "Memory allocation for name failed\n");
                freeList(&head);
                return 1;
             }
                strcpy(name, first_name);
                strcat(name, " ");
                strcat(name, last_name);
                // Trim trailing whitespace from name
                char *trimmedName = trimWhiteSpace(name);
        
                // Create and add new student to the list
                Student *newStudent = createStudent(id, gpa, trimmedName);
                if (!newStudent) {
                    fprintf(stderr, "Memory allocation for newStudent() failed\n");
                    freeList(&head);
                return 1;
                }
        
            addStudent(&head, newStudent);
        }
       
        } else if (strncmp(buffer, "REMOVE ", 7) == 0) {
            if (sscanf(buffer + 7, "%d", &id) == 1) {
                removeStudent(&head, id);
            }
        } else if (strncmp(buffer, "PRINT_BELOW ", 12) == 0) {
            if (sscanf(buffer + 12, "%f", &gpa) == 1) {
                printBelowGPA(head, gpa);
            }
        } else if (strncmp(buffer, "PRINT_ABOVE ", 12) == 0) {
            if (sscanf(buffer + 12, "%f", &gpa) == 1) {
                printAboveGPA(head, gpa);
            }
        } else if (strcmp(buffer, "SORT NAME") == 0) {
            sortByName(&head);
        } else if (strcmp(buffer, "SORT GPA") == 0) {
            sortByGPA(&head);
        }
    }
    
    // Free allocated memory
    freeList(&head);
    
    return 0;
}

// Create a new student node
Student* createStudent(int id, float gpa, char *name) {
    Student *newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) return NULL;
    
    newStudent->id = id;
    newStudent->gpa = gpa;
    
    // Allocate memory for name and copy it
    newStudent->name = (char*)malloc(strlen(name) + 1);
    if (!newStudent->name) {
        free(newStudent);
        return NULL;
    }
    strcpy(newStudent->name, name);
    
    newStudent->next = NULL;
    return newStudent;
}

// Add a student to the end of the list
void addStudent(Student **head, Student *newStudent) {
    if (!*head) {
        *head = newStudent;
        return;
    }
    
    Student *current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = newStudent;
}

// Print a single student's information
void printStudent(Student *student) {
    if (student) {
        printf("%d %.2f %s\n", student->id, student->gpa, student->name);
    }
}

// Print all students in the list
void printAll(Student *head) {
    Student *current = head;
    while (current) {
        printStudent(current);
        current = current->next;
    }
}

// Find a student by ID
Student *findStudent(Student *head, int id) {
    Student *current = head;
    while (current) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Print a student by ID
void printStudentById(Student *head, int id) {
    Student *student = findStudent(head, id);
    if (student) {
        printStudent(student);
    }
}

// Remove a student from the list by ID
void removeStudent(Student **head, int id) {
    if (!*head) return;
    
    if ((*head)->id == id) {
        Student *temp = *head;
        *head = (*head)->next;
        free(temp->name);
        free(temp);
        return;
    }
    
    Student *current = *head;
    while (current->next && current->next->id != id) {
        current = current->next;
    }
    
    if (current->next) {
        Student *temp = current->next;
        current->next = temp->next;
        free(temp->name);
        free(temp);
    }
}

// Print students with GPA below a specified threshold
void printBelowGPA(Student *head, float gpa) {
    Student *current = head;
    while (current) {
        if (current->gpa < gpa) {
            printStudent(current);
        }
        current = current->next;
    }
}

// Print students with GPA above or equal to a specified threshold
void printAboveGPA(Student *head, float gpa) {
    Student *current = head;
    while (current) {
        if (current->gpa >= gpa) {
            printStudent(current);
        }
        current = current->next;
    }
}

// Sort the list by name 
void sortByName(Student **head) {
    if (!*head || !(*head)->next) return;
    
    int swapped;
    Student *ptr1;
    Student *lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = *head;
        
        while (ptr1->next != lptr) {
            if (strcmp(ptr1->name, ptr1->next->name) > 0) {
                // Swap data (not pointers)
                int tempId = ptr1->id;
                float tempGpa = ptr1->gpa;
                char *tempName = ptr1->name;
                
                ptr1->id = ptr1->next->id;
                ptr1->gpa = ptr1->next->gpa;
                ptr1->name = ptr1->next->name;
                
                ptr1->next->id = tempId;
                ptr1->next->gpa = tempGpa;
                ptr1->next->name = tempName;
                
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Sort the list by GPA 
void sortByGPA(Student **head) {
    if (!*head || !(*head)->next) return;
    
    int swapped;
    Student *ptr1;
    Student *lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = *head;
        
        while (ptr1->next != lptr) {
            if (ptr1->gpa > ptr1->next->gpa) {
                // Swap data (not pointers)
                int tempId = ptr1->id;
                float tempGpa = ptr1->gpa;
                char *tempName = ptr1->name;
                
                ptr1->id = ptr1->next->id;
                ptr1->gpa = ptr1->next->gpa;
                ptr1->name = ptr1->next->name;
                
                ptr1->next->id = tempId;
                ptr1->next->gpa = tempGpa;
                ptr1->next->name = tempName;
                
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Free the entire linked list
void freeList(Student **head) {
    Student *current = *head;
    Student *next;
    
    while (current) {
        next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    
    *head = NULL;
}

// Trim trailing whitespace from string (does not remove leading or middle spaces)
char* trimWhiteSpace(char *str) {
    char *end;
    if (str == NULL) return NULL;

    // Find the end of the string
    end = str + strlen(str) - 1;

    // Move end pointer backward while it points to whitespace
    while (end >= str && isspace((unsigned char)*end)) {
        end--;
    }

    // Write new null terminator after the last non-whitespace character
    *(end + 1) = '\0';

    return str;
}
    
