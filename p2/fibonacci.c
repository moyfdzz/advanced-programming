#include <stdio.h>

int main()    
{
    int iNumber;

    scanf("%d", &iNumber);

    if (iNumber >= 1)
    {
        int iFirst, iSecond, iThird;

        iFirst = 0;
        iSecond = 1;

        printf("0");

        for (int iCounter = 1; iCounter < iNumber; iCounter++)
        {
            printf(" %d ", iSecond);
            iThird = iFirst + iSecond;
            iFirst = iSecond;
            iSecond = iThird;
        }

        printf("\n");
    }

    return 0;
}