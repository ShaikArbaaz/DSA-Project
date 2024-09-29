#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

int main() {
    char students[MAX_STUDENTS][100];
    int numStudents = 0;

    while (1) {
        printf("1. Create the list of students\n");
        printf("2. Insert a new student\n");
        printf("3. Delete a student\n");
        printf("4. Display student list\n");
        printf("5. Search for a student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of students: ");
                scanf("%d", &numStudents);

                for (int i = 0; i < numStudents; i++) {
                    printf("Enter student name %d: ", i + 1);
                    scanf("%s", &students[i]);
                }

                printf("Student list: ");
                for (int i = 0; i < numStudents; i++) {
                    printf("%s ", &students[i]);
                }
                printf("\n");
                
                break;

            case 2:
                printf("Enter the student's name to insert: ");
                char newStudent[100];
                scanf("%s", newStudent);

                printf("Enter the position (0-based index) to insert the student: ");
                int index;
                scanf("%d", &index);

                if (index >= 0 && index <= numStudents) {
                    for (int i = numStudents; i > index; i--) {
                        strcpy(students[i], students[i - 1]);
                    }
                    strcpy(students[index], newStudent);
                    numStudents++;
                } else {
                    printf("Invalid index.\n");
                }

                printf("Student list: ");
                for (int i = 0; i < numStudents; i++) {
                    printf("%s ", students[i]);
                }
                printf("\n");
                break;

            case 3:
                printf("Delete by name or position? (n/p): ");
                char choice3;
                scanf(" %c", &choice3);

                if (choice3 == 'n') {
                    printf("Enter the student's name to delete: ");
                    scanf("%s", newStudent);

                    int foundIndex = -1;
                    for (int i = 0; i < numStudents; i++) {
                        if (strcmp(students[i], newStudent) == 0) {
                            foundIndex = i;
                            break;
                        }
                    }

                    if (foundIndex != -1) {
                        for (int i = foundIndex; i < numStudents - 1; i++) {
                            strcpy(students[i], students[i + 1]);
                        }
                        numStudents--;

                        printf("Student list: ");
                        for (int i = 0; i < numStudents; i++) {
                            printf("%s ", students[i]);
                        }
                        printf("\n");
                    } else {
                        printf("Student not found.\n");
                    }
                } else if (choice3 == 'p') {
                    printf("Enter the position (0-based index) to delete: ");
                    scanf("%d", &index);

                    if (index >= 0 && index < numStudents) {
                        for (int i = index; i < numStudents - 1; i++) {
                            strcpy(students[i], students[i + 1]);
                        }
                        numStudents--;

                        printf("Student list: ");
                        for (int i = 0; i < numStudents; i++) {
                            printf("%s ", students[i]);
                        }
                        printf("\n");
                    } else {
                        printf("Invalid index.\n");
                    }
                } else {
                    printf("Invalid choice.\n");
                }
                break;

            case 4:
                printf("Student list: ");
                for (int i = 0; i < numStudents; i++) {
                    printf("%s ", students[i]);
                }
                printf("\n");
                break;

            case 5:
                printf("Enter the student's name to search: ");
                scanf("%s", newStudent);

                int foundIndex = -1;
                for (int i = 0; i < numStudents; i++) {
                    if (strcmp(students[i], newStudent) == 0) {
                        foundIndex = i;
                        break;
                    }
                }

                if (foundIndex != -1) {
                    printf("%s found at position %d\n", newStudent, foundIndex);
                } else {
                    printf("%s not found.\n", newStudent);
                }
                break;

            case 6:
                printf("Exiting the program...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}