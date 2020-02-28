/*
*   Author: Moisés Fernández Zárate A01197049
*   Date created: 25/02/2020
*
*   RandomGenerator.C
*   Hour of Code #1: implement a random generator algorithm in C.
*/
#include <stdio.h>
#include <time.h>
#include <unistd.h>
 
// This is equal to the biggest size of an integer (INT_MAX).
#define RAND_MAX ((1U << 31) - 1)

// Code implementation of the formula of a linear congruential sequence.
int rand();

// Global variable for the seed.
int seed = 0;

int main()
{
	printf("The max random number that can be generated: %d\n", RAND_MAX);
 
	for (int i = 0; i < 10; i++)
    {
        printf("Random %d: %d\n", i + 1, rand());
        sleep(1);
    }
 
	return 0;
}

int rand()
{
	return seed = (time(0) * 1103515245 + 12345) & RAND_MAX;
}