#include <stdio.h>
#include "color.h"

void select_choice();
void react_to_choice(int choice);
void add_task();

int main(void) {
    // Print the welcome message
    printf(MAGENTA "###########################\n");
    printf("#Welcome to the Todo List!#\n");
    select_choice();
}

void select_choice( ) {
    int choice;
    printf(MAGENTA "###########################\n");
    printf("1. Add a task\n");
    printf("2. View tasks\n");
    printf("3. Mark a task as done\n");
    printf("4. Delete a task\n");
    printf("5. Exit\n");
    printf(YELLOW "Please select an option: ");
    scanf("%d", &choice);
    react_to_choice(choice);
}

void react_to_choice (int choice) {
    switch (choice) {
        case 1:
            add_task();
            break;
        default:
            printf(RED "Invalid choice. Please try again.\n");
            break;
    }
}

void add_task() {
    char task[50];
    int choice;
    printf(YELLOW "Enter the task: ");
    scanf("%s", &task);
    printf(GREEN "Task '%s' added successfully!\n\n", task);

    select_choice(choice);
}