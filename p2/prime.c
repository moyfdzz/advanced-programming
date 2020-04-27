#include <stdio.h>

int main()    
{
    int iNumber;

    scanf("%d", &iNumber);

    if (iNumber > 1) 
    {
        for (int iCounter = 2; iCounter < iNumber; iCounter++)
        {
            if (iNumber % iCounter == 0) 
            {
                printf("The number is not prime.\n");

                return 0;
            }
        }

        printf("The number is prime.\n");
    }

    return 0;
}