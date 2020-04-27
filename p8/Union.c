/*
*   Author: Moisés Fernández Zárate A01197049
*   Date created: 13/03/2020
*
*   Union.c
*   A practice created to learn how to use a union.
*/

#include <stdio.h>
#include <float.h>
#include <string.h>

/*
*   I had a problem when receiving the input in the console, so I searched how to
*   clear the input buffer and I found how to do it in the following post of Dmitri
*   in stackoverflow: https://stackoverflow.com/a/7898362
*/
void clean_stdin(void);

// Here is the declaration of the union to store the information.
union myUnion {
    int integer;
    char string[100];
    double myDouble;
};

/*
*   main()
*   This is the main function where the flow of the program happens.
*/
int main()    
{   
    union myUnion u;

    printf("Enter an integer: ");
    scanf("%d", &u.integer);
    printf("Your integer %d storage size is %lu bytes.\n", u.integer, sizeof(u.integer));

    clean_stdin();

    printf("Enter a string: ");
    scanf("%s", u.string);
	printf("Your string %s storage size is %lu bytes.\n", u.string, sizeof(u.string));
    
    clean_stdin();

    printf("Enter a double: ");
    scanf("%lf", &u.myDouble);
    printf("Your double %lf storage size is %lu bytes, I can read any number from %g to %g in this data type.\n", u.myDouble, sizeof(u.myDouble), DBL_MIN, DBL_MAX);

    return 0;
}

void clean_stdin(void) {
    int ch;
    
    while ((ch = getchar()) != '\n' && ch != EOF) 
        ;
}