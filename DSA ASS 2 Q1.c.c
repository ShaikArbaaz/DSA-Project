#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a contact node in a doubly linked list
struct Node {
    char name[50];
    struct Node* prev;
    struct Node* next;
};

// Global variable for the head of the doubly linked list
struct Node* head = NULL;

// Function prototypes
void createList();
void insertContact();
void deleteContact();
void displayList();
void searchContact();

int main() {
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Create the list of contacts\n");
        printf("2. Insert a new contact\n");
        printf("3. Delete a contact\n");
        printf("4. Display contact list\n");
        printf("5. Search for a contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                createList();
                break;
            case 2:
                insertContact();
                break;
            case 3:
                deleteContact();
                break;
            case 4:
                displayList();
                break;
            case 5:
                searchContact();
                break;
            case 6:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while(choice != 6);

    return 0;
}

void createList() {
    int n, i;
    char contactName[50];

    printf("Enter the number of contacts: ");
    scanf("%d", &n);

    struct Node* temp = NULL;
    struct Node* tail = NULL;

    for (i = 0; i < n; i++) {
        printf("Enter contact name %d: ", i + 1);
        scanf("%s", contactName);

        struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
        strcpy(newNode->name, contactName);
        newNode->prev = NULL;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    printf("Contact list (forward): ");
    displayList();
}

void insertContact() {
    char contactName[50];
    int position, i = 0;

    printf("Enter the contact's name to insert: ");
    scanf("%s", contactName);
    printf("Enter the position (0-based index) to insert the contact: ");
    scanf("%d", &position);

    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    strcpy(newNode->name, contactName);
    newNode->prev = NULL;
    newNode->next = NULL;

    if (position == 0) {
        newNode->next = head;
        if (head != NULL)
            head->prev = newNode;
        head = newNode;
    } else {
        struct Node* temp = head;
        while (temp != NULL && i < position - 1) {
            temp = temp->next;
            i++;
        }

        if (temp == NULL) {
            printf("Position out of range. Inserting at the end.\n");
            temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
            newNode->prev = temp;
        } else {
            newNode->next = temp->next;
            newNode->prev = temp;
            if (temp->next != NULL)
                temp->next->prev = newNode;
            temp->next = newNode;
        }
    }

    printf("Contact list (forward): ");
    displayList();
}

void deleteContact() {
    char contactName[50];
    char choice;
    int position, i = 0;
    struct Node *temp = head;

    printf("Delete by name or position? (n/p): ");
    scanf(" %c", &choice);

    if (choice == 'n' || choice == 'N') {
        printf("Enter the contact's name to delete: ");
        scanf("%s", contactName);

        while (temp != NULL && strcmp(temp->name, contactName) != 0) {
            temp = temp->next;
        }
    } else if (choice == 'p' || choice == 'P') {
        printf("Enter the position (0-based index) to delete the contact: ");
        scanf("%d", &position);

        while (temp != NULL && i < position) {
            temp = temp->next;
            i++;
        }
    }

    if (temp == NULL) {
        printf("Contact not found.\n");
        return;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    free(temp);
    printf("Contact list (forward): ");
    displayList();
}

void displayList() {
    struct Node* temp = head;

    // Display forward list
    printf("Contact list (forward): ");
    if (temp == NULL) {
        printf("Contact list is empty.\n");
        return;
    }
    while (temp != NULL) {
        printf("%s <-> ", temp->name);
        if (temp->next == NULL) break; // Store the last node for backward traversal
        temp = temp->next;
    }
    printf("NULL\n");

    // Display backward list
    printf("Contact list (backward): ");
    while (temp != NULL) {
        printf("%s <-> ", temp->name);
        temp = temp->prev;
    }
    printf("NULL\n");
}

void searchContact() {
    char contactName[50];
    int position = 0;
    struct Node* temp = head;

    printf("Enter the contact's name to search: ");
    scanf("%s", contactName);

    while (temp != NULL && strcmp(temp->name, contactName) != 0) {
        temp = temp->next;
        position++;
    }

    if (temp == NULL) {
        printf("%s not found in the contact list.\n", contactName);
    } else {
        printf("%s found at positions %d.\n", contactName, position);
    }
}