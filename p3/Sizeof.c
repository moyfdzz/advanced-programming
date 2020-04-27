/*
*   Author: Moisés Fernández Zárate A01197049
*   Date created: 21/02/2020
*
*   Sizeof.c
*   A practice created to learn different types of data in C and the function sizeof()
*/

#include <stdio.h>
#include <float.h>

/*
*   I had a problem when receiving the input in the console, so I searched how to
*   clear the input buffer and I found how to do it in the following post of Dmitri
*   in stackoverflow: https://stackoverflow.com/a/7898362
*/
void clean_stdin(void);

/*
*   main()
*   This is the main function where the flow of the program happens.
*/
int main()    
{
    int iNumber;
    char cChar;
    double dDouble;
    
    printf("Enter an integer: ");
    scanf("%d", &iNumber);

    clean_stdin();

    printf("Enter a char: ");
    scanf("%c", &cChar);

    clean_stdin();

    printf("Enter a double: ");
    scanf("%lf", &dDouble);

    printf("Your integer %d storage size is %lu bytes.\n", iNumber, sizeof(iNumber));
    printf("Your char %c storage size is %lu bytes. And I can read it as %c or as %d.\n", cChar, sizeof(cChar), cChar, cChar);
    printf("Your double %lf storage size is %lu bytes, I can read any number from %g to %g in this data type.\n", dDouble, sizeof(dDouble), DBL_MIN, DBL_MAX);

    return 0;
}

void clean_stdin(void) {
    int ch;
    
    while ((ch = getchar()) != '\n' && ch != EOF) 
        ;
}