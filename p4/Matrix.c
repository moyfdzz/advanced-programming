/*
*   Author: Moisés Fernández Zárate A01197049
*   Date created: 21/02/2020
*
*   Matrix.c
*   A practice created to manage matrices using C.
*/
#include <stdio.h>

#define MATSIZE 2

/*
*   Function: fillMatrix(int iMat[MATSIZE][MATSIZE], char *sInfo)
*   This function receives values from the user to store them into a
*   2x2 matrix and also displays information about which matrix
*   the values belong to.
*   Parameters: int iMat[][]: the matrix where the user's values will 
*   be stored.
*   char *sInfo: the information about which matrix the values belong to.
*   Return value: None.
*/
void fillMatrix(int iMat[MATSIZE][MATSIZE], char *sInfo);

/*
*   Function: printMatrix(int iMat[MATSIZE][MATSIZE], char *sInfo)
*   This function receives a 2x2 matrix, prints all of its values, and
*   also displays information about which matrix the values belong to.
*   Parameters: int iMat[][]: the matrix that that will be printed.
*   char *sInfo: the information about which matrix the values belong to.
*   Return value: None.
*/
void printMatrix(int iMat[MATSIZE][MATSIZE], char *sInfo);

/*
*   Function: addMatrices(int iMatA[MATSIZE][MATSIZE], int iMatB[MATSIZE][MATSIZE], int iMatC[MATSIZE][MATSIZE])
*   This function receives three 2x2 matrices, two of them will be added and
*   the third one will be used to store the result of the addition.
*   Parameters: int iMatA[][]: the first matrix that will be added.
*   int iMatB[][]: the second matrix that will be added.
*   int iMatC[][]: the third matrix where the result of the addition is stored.
*   Return value: None.
*/
void addMatrices(int iMatA[MATSIZE][MATSIZE], int iMatB[MATSIZE][MATSIZE], int iMatC[MATSIZE][MATSIZE]);

/*
*   Function: subtractMatrices(int iMatA[MATSIZE][MATSIZE], int iMatB[MATSIZE][MATSIZE], int iMatC[MATSIZE][MATSIZE])
*   This function receives three 2x2 matrices, two of them will be subtracted and
*   the third one will be used to store the result of the subtraction.
*   Parameters: int iMatA[][]: the first matrix that will be subtracted.
*   int iMatB[][]: the second matrix that will be subtracted.
*   int iMatC[][]: the third matrix where the result of the subtraction is stored.
*   Return value: None.
*/
void subtractMatrices(int iMatA[MATSIZE][MATSIZE], int iMatB[MATSIZE][MATSIZE], int iMatC[MATSIZE][MATSIZE]);

/*
*   Function: subtractMatrices(int iMatA[MATSIZE][MATSIZE], int iMatB[MATSIZE][MATSIZE], int iMatC[MATSIZE][MATSIZE])
*   This function receives three 2x2 matrices, two of them will be multiplied and
*   the third one will be used to store the result of the multiplication.
*   Parameters: int iMatA[][]: the first matrix that will be multiplied.
*   int iMatB[][]: the second matrix that will be multiplied.
*   int iMatC[][]: the third matrix where the result of the multiplication is stored.
*   Return value: None.
*/
void multiplyMatrices(int iMatA[MATSIZE][MATSIZE], int iMatB[MATSIZE][MATSIZE], int iMatC[MATSIZE][MATSIZE]);

/*
    main()
    This is the main function where the flow of the program happens.
*/
int main()
{
    int iMatA[MATSIZE][MATSIZE];
    int iMatB[MATSIZE][MATSIZE];
    int iMatC[MATSIZE][MATSIZE];

    fillMatrix(iMatA, "Enter the values for the matrix A");
    fillMatrix(iMatB, "Enter the values for the matrix B");
    printMatrix(iMatA, "Here is the matrix A");
    printMatrix(iMatB, "Here is the matrix B");

    addMatrices(iMatA, iMatB, iMatC);
    printMatrix(iMatC, "Here is the result of adding the matrices A and B");

    subtractMatrices(iMatA, iMatB, iMatC);
    printMatrix(iMatC, "Here is the result of subtracting the matrices A and B");

    multiplyMatrices(iMatA, iMatB, iMatC);
    printMatrix(iMatC, "Here is the result of multiplying the matrices A and B");

    return 0;
}

void fillMatrix(int iMat[MATSIZE][MATSIZE], char *sInfo)
{
    printf("%s\n", sInfo);

    for (int iRows = 0; iRows < MATSIZE; iRows++) 
    {
        for (int iColumns = 0; iColumns < MATSIZE; iColumns++)
        {
            scanf("%d", &iMat[iRows][iColumns]);
        }
    }
}

void printMatrix(int iMat[MATSIZE][MATSIZE], char *sInfo)
{
    printf("%s\n", sInfo);

    for (int iRows = 0; iRows < MATSIZE; iRows++) 
    {
        for (int iColumns = 0; iColumns < MATSIZE; iColumns++)
        {
            printf("%d ", iMat[iRows][iColumns]);
        }

        printf("\n");
    }
}

void addMatrices(int iMatA[MATSIZE][MATSIZE], int iMatB[MATSIZE][MATSIZE], int iMatC[MATSIZE][MATSIZE])
{
    for (int iRows = 0; iRows < MATSIZE; iRows++) 
    {
        for (int iColumns = 0; iColumns < MATSIZE; iColumns++)
        {
            iMatC[iRows][iColumns] = iMatA[iRows][iColumns] + iMatB[iRows][iColumns];
        }
    }
}

void subtractMatrices(int iMatA[MATSIZE][MATSIZE], int iMatB[MATSIZE][MATSIZE], int iMatC[MATSIZE][MATSIZE])
{
    for (int iRows = 0; iRows < MATSIZE; iRows++) 
    {
        for (int iColumns = 0; iColumns < MATSIZE; iColumns++)
        {
            iMatC[iRows][iColumns] = iMatA[iRows][iColumns] - iMatB[iRows][iColumns];
        }
    }
}

void multiplyMatrices(int iMatA[MATSIZE][MATSIZE], int iMatB[MATSIZE][MATSIZE], int iMatC[MATSIZE][MATSIZE])
{
    for (int iRows = 0; iRows < MATSIZE; iRows++) 
    {
        for (int iColumns = 0; iColumns < MATSIZE; iColumns++)
        {
            iMatC[iRows][iColumns] = 0;
        }
    }

    for (int iRows = 0; iRows < MATSIZE; iRows++) 
    {
        for (int iColumns = 0; iColumns < MATSIZE; iColumns++)
        {
            for (int iCounter = 0; iCounter < MATSIZE; iCounter++)
            {
                iMatC[iRows][iColumns] += iMatA[iRows][iCounter] * iMatB[iCounter][iColumns];
            }
        }
    }
}