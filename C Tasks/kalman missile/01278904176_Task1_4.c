/*
 * File: main.c
 * Author: Ahmed Mahmoud
 * Description: Generate a fusion of 2 given arrays of data
 * Date: [14/8/2023]
 */

/* Header Files */
#include <stdio.h>  // Standard I/O functions
#include <stdlib.h> // Standard library functions

/* Macros */
#define Initial_Velocity 30
#define Initial_Angle 46
#define mpu6050_accuracy 0.79
#define bno55_accuracy 0.92
#define size 10

/* Function Declarations */
void Show_data(float optimal[]);
void Fair_Average(float mpu6050[], float bno55[], float optimal[]);
void Good_Average(float mpu6050[], float bno55[], float optimal[]);
void Hero_Average(float mpu6050[], float bno55[], float optimal[]);

/* Main Function */
int main()
{

    //Hard coded data
    float mpu6050[size] = {0.0, 11.68, 18.95, 23.56, 25.72, 25.38, 22.65, 18.01, 10.14, -0.26};
    float bno55[size] = {0.0,9.49, 16.36, 21.2, 23.16, 22.8, 19.5, 14.85, 6.79, -2.69};

    int choice;
    float optimal[size] = {0};

    printf("1. Fair\n");
    printf("2. Good\n");
    printf("3. Hero\n");
    printf("4. Legend\n");

    do
    {
        printf("\nChoose approach : ");
        scanf("%d", &choice);
    }
    while(choice < 1 || choice > 4);


    switch (choice)
    {
    case 1:
        Fair_Average(mpu6050, bno55, optimal);
        Show_data(optimal);
        break;
    case 2:
        Good_Average(mpu6050, bno55, optimal);
        Show_data(optimal);
        break;
    case 3:
        Hero_Average(mpu6050, bno55, optimal);
        Show_data(optimal);
        break;
    case 4:
        printf("\nUnfinished Yet\n\n");
        break;
    }

    // to repeat the whole program instead of exiting the terminal and re-open it
    main();

    return 0;
}

/* Function Definitions */
/**
 * @brief print the data
 *
 * @param float array describe the mpu6050 sensor's data
 * @return void
 */
void Show_data(float optimal[])
{
    // Function logic
    printf("\n");
    for(int i = 0; i < size ; i++)
        printf("%.3f ",optimal[i]);
    printf("\n\n");
}


/**
 * @brief calculate the average values of 2 given arrays
 *
 * @param float array describe the mpu6050 sensor's data
 * @param float array describe the bno55 sensor's data
 * @param float array describe the calculated data
 * @return void
 */
void Fair_Average(float mpu6050[], float bno55[], float optimal[])
{
    // Function logic
    for(int i = 0; i < size ; i++)
        optimal[i] = (mpu6050[i] + bno55[i]) / 2;
}

/**
 * @brief calculate the average values of 2 given arrays considering the accuracy of each sensor
 *
 * @param float array describe the mpu6050 sensor's data
 * @param float array describe the bno55 sensor's data
 * @param float array describe the calculated data
 * @return void
 */
void Good_Average(float mpu6050[], float bno55[], float optimal[])
{
    // Function logic
    for(int i = 0; i < size ; i++)
        optimal[i] = (mpu6050[i] * mpu6050_accuracy + bno55[i] * bno55_accuracy) / (bno55_accuracy + mpu6050_accuracy);
}

/**
 * @brief calculate the average values of 2 given arrays considering the accuracy of each sensor and gives more accurate output
 *
 * @param float array describe the mpu6050 sensor's data
 * @param float array describe the bno55 sensor's data
 * @param float array describe the calculated data
 * @return void
 */
void Hero_Average(float mpu6050[], float bno55[], float optimal[])
{
    // Function logic

    float kg = (1 - bno55_accuracy) / (1 - bno55_accuracy + 1 - mpu6050_accuracy);

    for(int i = 0; i < size ; i++)
        optimal[i] = bno55[i] + kg * (mpu6050[i] - bno55[i]);
}
