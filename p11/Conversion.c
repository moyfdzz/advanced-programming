/*
*   Author: Moisés Fernández 
*   ID: A01197049
*   Date: 27/03/2020
*   P11. Conversion
*/
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int asciiHEXToInt(char *s)
{
    int size = strlen(s);
    int aux = 0;

    while(*s != '\0' && isxdigit(*s))
    {
        aux++;
        s++;
    }

    if (aux != size)
    {
        printf("Error: Invalid characters. \n");

        return -1;
    }

    int result = 0;
    int val = 0;
    int exponent = 0;

    while(aux > 0)
    {
        s--;

        if (*s >= '0' && *s <= '9')
        {
            val = *s - 48;
        }
        else if (*s >= 'a' && *s <= 'f')
        {
            val = *s - 87;
        }
        else if (*s >= 'A' && *s <= 'F')
        {
            val = *s - 55;
        }

        result += val * pow(16, exponent);

        aux--;
        exponent++;
    }

    return result;
}

int asciiBINToInt(char *s){
    int index = 0;
    int size = strlen(s);

    while(*s != '\0' && (*s == '0' || *s == '1'))
    {
        index++;
        s++;
    }

    if( index != size)
    {
        printf("Error: Invalid characters. \n");

        return -1;
    }

    s -= 1;

    int result = 0;
    int val = 0;
    int exponent = 0;
    while(*s == '0' || *s == '1'){
    val = *s - 48;
    result += val * pow(2,exponent);
    exponent++;
    s--;
    }

    return result;
}

int asciiOCTToInt(char *s){
    int size = strlen(s);
    int aux = 0;

    while(*s != '\0' && *s >= '0' && *s <= '7')
    {
        aux++;
        s++;
    }

    if( aux != size)
    {
        printf("Error: Invalid characters. \n");

        return -1;
    }

    int result = 0;
    int val = 0;
    int exponent = 0;

    while(aux > 0){
        s--;

        if(*s >= '0' && *s <= '9')
        {
            val = *s - 48;
        }
        else if (*s >= 'a' && *s <= 'f')
        {
            val = *s - 87;
        }
        else if (*s >= 'A' && *s <= 'F')
        {
            val = *s - 55;
        }

        result += val * pow(8,exponent);

        aux--;
        exponent++;
    }

    return result;
}

int divideByTwo(int *i)
{
  int num = *i;

  num = num >>1;

  return num;
}

int multiplyByTwo(int *i)
{
  int num = *i;

  num = num <<1;

  return num;
}

int main(void) {
  int iRes = 0;

  do {
    printf("Enter a number (1, 2, 3, 4, 5):\n");
    printf("1) Convert hexadecimal to decimal\n");
    printf("2) Convert bits to decimal\n");
    printf("3) Convert octadecimal to decimal\n");
    printf("4) Divide a number by 2 in bits\n");
    printf("5) Multiply a number by 2 in bits\n");
    scanf("%d", &iRes);

    char cBinaryArr[9] = "";
    char cHexArr[9] = "";
    char cOctArr[9] = "";
    int iNumber1 = 0;
    int iNumber2 = 0;
    char *pointer = NULL;
    int *pointer2 = NULL;
  
    switch(iRes){
      case 1:
        printf("Escribe un numero heaxadecimal de maximo 8 numeros\n");
        scanf("%s",cHexArr);

        pointer = cHexArr;
        printf("Integer: %d\n", asciiHEXToInt(pointer));
        //printf("%s",cHexArr);
        break;
      case 2:
        printf("Escribe un numero en bits de maximo 8 numeros\n");
        scanf("%s",cBinaryArr);
        printf("%s\n", cBinaryArr);
        pointer = cBinaryArr;
        printf("Integer: %d\n", asciiBINToInt(pointer));
        break;
      case 3:
        printf("Escribe un numero octadecimal de maximo 8 numeros\n");
        scanf("%s",cOctArr);

        pointer = cOctArr;
        printf("Integer: %d\n", asciiOCTToInt(pointer));
        break;
      case 4:
        printf("Escribe un numero entero\n");
        scanf("%d",&iNumber1);

        pointer2 = &iNumber1;
        //printf("\nNumero: %d\n", *pointer2);
        printf("Resultado: %d\n", divideByTwo(pointer2));
        break;
      case 5:
        printf("Escribe un numero entero\n");
        scanf("%d",&iNumber2);

        pointer2 = &iNumber2;
        //printf("\nNumero: %d\n", *pointer2);
        printf("Resultado: %d\n", multiplyByTwo(pointer2));
        break;
    }

  }while(iRes != 6);

  return 0;
}