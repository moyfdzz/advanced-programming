/*
*   Author: Moisés Fernández Zárate A01197049
*   Date created: 22/02/2020
*
*   Recursion.c
*   A practice created to learn recursion in C.
*/
#include <stdio.h>

/*
*   Function: long long int factorial(int iNumFact)
*   This function calculates the factorial of a given number.
*   Parameters: int iNumFact, the given number to calculate the factorial.
*   Return value: long long int, the factorial of the given number.
*/
long long int factorial(int iNumFact);

/*
*   Function: fibonacci(int iNumFibo)
*   This function calculates the N numbers on the Fibonacci sequence.
*   Parameters: int iNumFibo, the given number to calculate the N numbers on 
*   the Fibonacci sequence.
*   Return value: int, the nth number of the Fibonacci sequence.
*/
int fibonacci(int iNumFibo);

/*
*   main()
*   This is the main function where the flow of the program happens.
*/
int main(void)
{
    int iNumFact;
    int iNumFibo;

    printf("Enter a number to calculate its factorial: ");
    scanf("%d", &iNumFact);

    printf("Enter a number to calculate N numbers on the Fibonacci sequence: ");
    scanf("%d", &iNumFibo);

    printf("Factiorial of %d: %lld\n", iNumFact, factorial(iNumFact));
    printf("First %d numbers on the Fibonacci sequence\n", iNumFibo);
    
    for (int i = 1; i <= iNumFibo; i++)
    {
        printf("%d ", fibonacci(i));
    }

    printf("\n");

    return 0;
}

long long int factorial(int iNumFact)
{
    if (iNumFact == 0)
    {
        return 1;
    }

    return factorial(iNumFact - 1) * iNumFact;
}

int fibonacci(int iNumFibo) 
{
    if (iNumFibo == 1)
    {
        return 0;
    }

    if (iNumFibo == 2)
    {
        return 1;
    }

    return fibonacci(iNumFibo - 1) + fibonacci(iNumFibo - 2);
}