/*
*   Author: Moisés Fernández Zárate A01197049
*   Date created: 22/02/2020
*
*   Pointers.c
*   A practice to learn pointer arithmetic in C.
*/
#include <stdio.h>
#include <string.h>

/*
*   main()
*   This is the main function where the flow of the program happens.
*/
int main(void)
{
    char word[5];

    printf("Enter the string: ");
    scanf("%s", word);

    for (int i = 0; i < strlen(word); i++)
    {
        
    }

    int *a = 4;
    int *e = 3;
    int *i = 1;
    int *o = 0;
    int *u = 2;

    return 0;
}