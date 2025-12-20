#include <stdio.h>
#include "color.h"
#include <string.h>

//prototyping functions
void select_choice();
void react_to_choice(int choice);
void add_task();
void view_tasks();
void modify_task();
void delete_task();
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
        select_choice();
        break;
    case 2:
        view_tasks();
        select_choice();
        break;
    case 3:
        modify_task();
        select_choice();
        break;  
    case 4:
        delete_task();
        select_choice();
        break;
    case 5:
        printf(GREEN "Goodbye!\n");
	break;
    default:
        printf(RED "Invalid choice. Please try again.\n");
        select_choice();
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
    fprintf(todoFile, "%s [NOT COMPLETED]\n", task);
    fclose(todoFile);

    // Print success message
    printf(GREEN "Task '%s' added successfully!\n\n", task);
}

void view_tasks(){
    char task[100];
    int count = 1;
    todoFile = fopen("todo.txt", "r");
    printf("\n");
    while (fgets(task, sizeof(task), todoFile)) {
        if (strstr(task, "[DONE]") != NULL) {
            printf(GREEN "%d. %s", count, task);
        } else {
            printf(RED "%d. %s", count, task);
        }
        count++;
    }
    fclose(todoFile);
}

void modify_task() {
    int task_number;
    char task[100];
    FILE *todoFile2 = NULL;

    printf(YELLOW "Enter the task number to modify: ");
    scanf("%d", &task_number);

    //open 2 files, one for reading and one for writing, if the line is not the one to be modified, write it to the new file, clone the files afterwards 
    todoFile = fopen("todotempt.txt", "w");
    todoFile2 = fopen("todo.txt", "r");
    int current_line = 1;
    while (fgets(task, sizeof(task), todoFile2)) {
        if (current_line != task_number) {
            fputs(task, todoFile);
        } else {
            char *bracket = strchr(task, '['); // Find the first occurrence of '['
                int index = bracket - task; // pointer math to find the index needed
                char temp[100];
                strncpy(temp, task, index);  
                temp[index] = '\0'; // need to add null terminator        
                fprintf(todoFile, "%s[DONE]\n", temp);
            }
        current_line++;
        }
        

    fclose(todoFile2);
    fclose(todoFile);
    //swapping
    remove("todo.txt");
    rename("todotempt.txt", "todo.txt");

    //clear random buffer
    size_t len = strlen(task);
    if (len > 0 && task[len - 1] == '\n') {
        task[len - 1] = '\0';
    }

    printf(GREEN "Task '%s' modified successfully!\n\n", task);
}

void delete_task() {
    int task_number;
    char task[100];
    FILE *todoFile2 = NULL;

    printf(YELLOW "Enter the task number to delete: ");
    scanf("%d", &task_number);

    //open 2 files, one for reading and one for writing, if the line is not the one to be deleted, write it to the new file, clone the files afterwards 
    todoFile = fopen("todotempt.txt", "w");
    todoFile2 = fopen("todo.txt", "r");
    int current_line = 1;
    while (fgets(task, sizeof(task), todoFile2)) {
        if (current_line != task_number) {
            fputs(task, todoFile);
        }
        current_line++;
    }

    fclose(todoFile2);
    fclose(todoFile);
    //swapping
    remove("todo.txt");
    rename("todotempt.txt", "todo.txt");

    //clear random buffer
    size_t len = strlen(task);
    if (len > 0 && task[len - 1] == '\n') {
        task[len - 1] = '\0';
    }

    printf(GREEN "Task '%s' deleted successfully!\n\n", task);
}
