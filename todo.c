#include <stdio.h>
#include "color.h"
#include <string.h>

void select_choice();
void react_to_choice(int choice);
void add_task();
// defining file
FILE *todoFile = NULL;

int main(void)
{
    // Print the welcome message
    printf(MAGENTA "###########################\n");
    printf("#Welcome to the Todo List!#\n");
    select_choice();
}

void select_choice()
{
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

void react_to_choice(int choice)
{
    switch (choice)
    {
    case 1:
        add_task();
        //recall choice to keep the process going
        select_choice(choice);
        break;
    default:
        printf(RED "Invalid choice. Please try again.\n");
        select_choice(choice);
        break;
    }
}

void add_task()
{
    char task[100];
    printf(YELLOW "Enter the task: ");
    getchar(); // Clear the input buffer
    fgets(task, sizeof(task), stdin);

    // Remove newline character from the input
    size_t len = strlen(task);
    if (len > 0 && task[len - 1] == '\n'){
        task[len - 1] = '\0'; // Replaces newline with null terminator
    }

    // Open the file in append mode
    todoFile = fopen("todo.txt", "a");
    fprintf(todoFile, "%s\n", task);
    fclose(todoFile);

    // Print success message
    printf(GREEN "Task '%s' added successfully!\n\n", task);
}