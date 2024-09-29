#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a contact node
struct Contact {
    char name[50];
    struct Contact *next;
};

// Function to create a new contact node
struct Contact* createContact(char name[]) {
    struct Contact *newContact = ( struct Contact*) malloc(sizeof(struct Contact));
    strcpy(newContact->name, name);
    newContact->next = NULL;
    return newContact;
}

// Function to insert a new contact at a specific position
void insertContact(struct Contact **head, char name[], int position) {
    struct Contact *newContact = createContact(name);
    
    if (position == 0) {
        newContact->next = *head;
        *head = newContact;
    } else {
        struct Contact *temp = *head;
        for (int i = 0; i < position - 1 && temp->next != NULL; i++) {
            temp = temp->next;
        }
        newContact->next = temp->next;
        temp->next = newContact;
    }
}

// Function to delete a contact by name or position
void deleteContact(struct Contact **head, char name[], int position) {
    if (*head == NULL) {
        printf("Contact list is empty.\n");
        return;
    }
    
    struct Contact *temp = *head, *prev = NULL;
    
    // Delete by name
    if (position == -1) {
        while (temp != NULL && strcmp(temp->name, name) != 0) {
            prev = temp;
            temp = temp->next;
        }
    } else { // Delete by position
        for (int i = 0; i < position && temp != NULL; i++) {
            prev = temp;
            temp = temp->next;
        }
    }
    
    if (temp == NULL) {
        printf("Contact not found.\n");
        return;
    }
    
    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    free(temp);
}

// Function to display all contacts in the list
void displayContacts(struct Contact *head) {
    if (head == NULL) {
        printf("Contact list is empty.\n");
        return;
    }
    
    printf("Contact list: ");
    struct Contact *temp = head;
    while (temp != NULL) {
        printf("%s -> ", temp->name);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to search for a contact by name
void searchContact(struct Contact *head, char name[]) {
    if (head == NULL) {
        printf("Contact list is empty.\n");
        return;
    }
    
    struct Contact *temp = head;
    int position = 0;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
        position++;
    }
    
    if (temp == NULL) {
        printf("%s not found.\n", name);
    } else {
        printf("%s found at position %d\n", name, position);
    }
}

// Function to free memory allocated for the linked list
void freeContacts(struct Contact **head) {
    struct Contact *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main() {
    struct Contact *head = NULL;
    int choice, position;
    char name[50];
    
    do {
        printf("\n1. Create the list of contacts\n");
        printf("2. Insert a new contact\n");
        printf("3. Delete a contact\n");
        printf("4. Display contact list\n");
        printf("5. Search for a contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                {
                    int numContacts;
                    printf("Enter the number of contacts: ");
                    scanf("%d", &numContacts);
                    
                    for (int i = 0; i < numContacts; i++) {
                        printf("Enter contact name %d: ", i + 1);
                        scanf("%s", name);
                        insertContact(&head, name, i);
                    }
                    
                    displayContacts(head);
                }
                break;
            case 2:
                printf("Enter the contact's name to insert: ");
                scanf("%s", name);
                printf("Enter the position (0-based index) to insert the contact: ");
                scanf("%d", &position);
                insertContact(&head, name, position);
                displayContacts(head);
                break;
            case 3:
                {
                    char deleteChoice;
                    printf("Delete by name or position? (n/p): ");
                    scanf(" %c", &deleteChoice);
                    
                    if (deleteChoice == 'n') {
                        printf("Enter the contact's name to delete: ");
                        scanf("%s", name);
                        deleteContact(&head, name, -1);
                    } else if (deleteChoice == 'p') {
                        printf("Enter the position (0-based index) to delete the contact: ");
                        scanf("%d", &position);
                        deleteContact(&head, name, position);
                    } else {
                        printf("Invalid choice.\n");
                    }
                    
                    displayContacts(head);
                }
                break;
            case 4:
                displayContacts(head);
                break;
            case 5:
                printf("Enter the contact's name to search: ");
                scanf("%s", name);
                searchContact(head, name);
                break;
            case 6:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
        
    } while (choice != 6);
    
    // Free memory before exiting
    freeContacts(&head);
    
    return 0;
}