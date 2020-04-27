/*
*   Author: Moisés Fernández 
*   ID: A01197049
*   Date: 27/03/2020
*   P10. Malloc
*/
#include <stdio.h>
#include <stdlib.h>

// Function that will manage the string received from the keyboard.
void extremelyLargeString(int size, char *ptr)
{
    int index = 0;
    char aux;

    while ((aux = getchar()) && aux != '\n') 
    {
        if (index < size)
        {
            ptr[index] = aux;
        }
        else
        {
            ptr = realloc(ptr, (size + 3) * sizeof(char));
            size += 3;
            ptr[index] = aux;
        }
    
        index++;
    }

    if(ptr[index - 1] != '$') 
    {
        printf("Error: Escape character not introduced \n");
    }
    else
    {
        printf("String: %s\n", ptr);
    }
}

// Main function.
int main(void) 
{
    int size = 3;

    char *ptr = NULL;

    ptr = malloc(sizeof(char) * size); 

    printf("Escape character: $\n");
    printf("Introduce a extremely large string: ");

    extremelyLargeString(size, ptr);

    // To free any allocated memory.
    free(ptr);

    return 0;
}