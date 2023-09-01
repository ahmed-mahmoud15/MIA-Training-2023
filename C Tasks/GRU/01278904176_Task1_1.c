/*
 * File: GRU.c
 * Author: Ahmed Mahmoud
 * Description: Printing GRU to console screen
 * Date: [12/8/2023]
 */

/* Header Files */
#include <stdio.h>  // Standard I/O functions
#include <stdlib.h> // Standard library functions

/* Macros */

/* Function Declarations */

void normal_print_GRU(void);

void bonus_print_GRU(void);

/* Main Function */
int main()
{

    int choice;
    do
    {
        printf("Enter 0 or 1\n");
        scanf("%d",&choice);
    }
    while(choice != 0 && choice != 1);

    if(choice)
        bonus_print_GRU();
    else
        normal_print_GRU();

    return 0;
}

/* Function Definitions */
/**
 * @brief this function prints GRU normally on terminal screen
 *
 * @param void.
 * @return void.
 */
void normal_print_GRU()
{
    // Function logic
    printf("GRU");
}

/**
 * @brief this function prints GRU with astreics on terminal screen
 *
 * @param void.
 * @return void.
 */
void bonus_print_GRU()
{
    // Function logic
    printf("*****    ****      *    *\n");
    printf("*        *   *     *    *\n");
    printf("*  **    ****      *    *\n");
    printf("*   *    *   *     *    *\n");
    printf("*****    *    *    ******\n");
}
