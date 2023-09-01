/*
 * File: countingDown.c
 * Author: Ahmed Mahmoud
 * Description: program to count down from given number.
 * Date: [12/8/2023]
 */

/* Header Files */
#include <stdio.h>  // Standard I/O functions
#include <stdlib.h> // Standard library functions
#include <unistd.h> // library contains sleep function

/* Macros */


/* Function Declarations */
void count_down(int counter);

/* Main Function */
int main() {

    int counter;

    do
    {
        printf("Enter number higher than 0: ");
        scanf("%d",&counter);
    }
    while(counter <= 0);

    count_down(counter);
    printf("\nBlast off to the moon!\n");

    return 0;
}

/* Function Definitions */
/**
 * @brief this function prints numbers descendingly from "counter" parameter to 1
 *
 * @param int counter.
 * @return Void.
 */
void count_down(int counter)
{
    // Function logic
    for(int i = counter ; i > 0; i--)
    {
        printf("%d\n",i);
        sleep(1);  // sleep function takes an integer refer to how many seconds the printing will delay

        //delete \n from the previous print function the uncomment the following line to see this good animation :)
        //printf("\b");
    }

}
