/*
 * File: task_manager.c
 * Author: Ahmed Mahmoud
 * Description: To-Do list
 * Date: [13/8/2023]
 */

/* Header Files */
#include <stdio.h>  // Standard I/O functions
#include <stdlib.h> // Standard library functions
#include <string.h> // string library functions

/* Macros */

/* Structs */

typedef struct task
{
    int id;
    char description[100];
    int checked;
} task;

/* Function Declarations */

void Add_Task(task[], int*);
void View_Tasks(task[], int*);
void Remove_Task(task[], int*);
void Complete_Task(task[], int*);

/* Main Function */
int main()
{
    task tasks[100];
    int option, size = 0;

    printf("Minions Task Manager\n");
    printf("1. Add Task\n");
    printf("2. View Tasks\n");
    printf("3. Remove Task\n");
    printf("4. Complete Task\n");
    printf("5. Exit\n");

    do
    {
        //validate the input option
        do
        {
            printf("\nSelect an Option: ");
            fflush(stdin);
            scanf("%d", &option);
        }
        while(option < 1 || option > 5);

        switch (option)
        {
        case 1:
            Add_Task(tasks, &size);
            break;
        case 2:
            View_Tasks(tasks, &size);
            break;
        case 3:
            Remove_Task(tasks, &size);
            break;
        case 4:
            Complete_Task(tasks, &size);
            break;
        case 5:
            break;
        }
    }
    while(option != 5);

    printf("\nExiting Minions Task Manager. Have a great day!\n");

    return 0;
}

/* Function Definitions */
/**
 * @brief this function adds new tasks to the to To-Do list
 *
 * @param array of task struct.
 * @param pointer to the number of tasks created.
 * @return void.
 */
void Add_Task(task tasks[], int* size)
{
    // Function logic
    tasks[*size].id = *size + 1;
    tasks[*size].checked = 0;
    printf("Enter Task Description : ");
    fflush(stdin);
    gets(tasks[*size].description);

    printf("\nTask Added Succefully\n");
    (*size)++;
}

/**
 * @brief this function views all tasks in the to To-Do list
 *
 * @param array of task struct.
 * @param pointer to the number of tasks created.
 * @return void.
 */
void View_Tasks(task tasks[], int* size)
{
    // Function logic
    printf("ID\t|\tDescription\t|\tCompleted?\n");
    printf("================================================\n");
    for(int i = 0 ; i < *size ; i++)
    {
        printf("%d\t|", tasks[i].id);

        if(strlen(tasks[i].description) <= 16 )
            printf("\t%s\t|\t", tasks[i].description);
        else
            printf("%s\t|\t", tasks[i].description);

        printf("%s\n", (tasks[i].checked)? "Yes" : "No");
    }
}

/**
 * @brief this function remove tasks to the to To-Do list by its ID
 *
 * @param array of task struct.
 * @param pointer to the number of tasks created.
 * @return void.
 */
void Remove_Task(task tasks[], int* size)
{
    // Function logic

    if (*size == 0)
    {
        printf("No Tasks to remove\n");
        return;
    }
    int removed_ID;
    task temp_task;

    printf("Enter task ID to remove : ");
    fflush(stdin);
    scanf("%d", &removed_ID);

    while(removed_ID < 1 || removed_ID > *size)
    {
        printf("Enter Valid task ID : ");
        fflush(stdin);
        scanf("%d", &removed_ID);
    }

    for(int i = removed_ID - 1 ; i < *size ; i++)
    {
        temp_task = tasks[i];
        tasks[i] = tasks[i + 1];
        tasks[i + 1] = temp_task;
        (tasks[i].id)--;
    }

    printf("\nTask Removed Succefully\n");
    (*size)--;
}

/**
 * @brief this function selects the task which has been completed
 *
 * @param array of task struct.
 * @param pointer to the number of tasks created.
 * @return void.
 */
void Complete_Task(task tasks[], int* size)
{
    // Function logic
    if (*size == 0)
    {
        printf("No Tasks to complete\n");
        return;
    }
    int completed_ID;

    printf("Enter task ID to complete : ");
    fflush(stdin);
    scanf("%d", &completed_ID);

    while(completed_ID < 1 || completed_ID > *size)
    {
        printf("Enter Valid task ID : ");
        fflush(stdin);
        scanf("%d", &completed_ID);
    }

    if(tasks[completed_ID - 1].checked == 1)
        printf("\nThis Task is Already Completed\n");
    else
    {
        tasks[completed_ID - 1].checked = 1;
        printf("\nTask Completed Successfully\n");
    }
}
