/*
*   Author: Moisés Fernández 
*   ID: A01197049
*   Date: 27/03/2020
*   Hour of Code 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

/*
*   Function to generate a new ID by shifting the string.
*   Parameters: str, the string that will be shifted.
*               shiftBy, by how much the string will be shifted.
*   Return value: the string that resulted from shifting the input.
*/
char *shiftString(char *str, int shiftBy);

/*
*   Function to delete blank spaces from a string.
*   Parameters: s, a string.
*   Return value: none.
*/
void deleteBlankSpaces(char *s);

// Struct to store an agent.
struct Agent
{
    char ID[4];
    char input[1000];
};

// Main function.
int main(void)
{
    char *found;
    char input[1000];
    struct Agent *a = (struct Agent *)malloc(sizeof(struct Agent));
    
    printf("Escribe números separados por coma\n");
    gets(input);
    deleteBlankSpaces(input);
    found = strtok(input, ",");

    printf("Escribe los primeros 4 caracteres de tu ID\n");
    gets(a->ID);

    while (found)
    {
        if (!strcmp(found, "uno"))
        {
            strcat(a->input, "1");
        }
        else if (!strcmp(found, "dos"))
        {
            strcat(a->input, "2");
        }
        else if (!strcmp(found, "tres"))
        {
            strcat(a->input, "3");
        }
        else if (!strcmp(found, "cuatro"))
        {
            strcat(a->input, "4");
        }
        else if (!strcmp(found, "cinco"))
        {
            strcat(a->input, "5");
        }
        else if (!strcmp(found, "seis"))
        {
            strcat(a->input, "6");
        }
        else if (!strcmp(found, "siete"))
        {
            strcat(a->input, "7");
        }
        else if (!strcmp(found, "ocho"))
        {
            strcat(a->input, "8");
        }
        else if (!strcmp(found, "nueve"))
        {
            strcat(a->input, "9");
        }
        else if (!strcmp(found, "diez"))
        {
            strcat(a->input, "10");
        }
        else if (!strcmp(found, "once"))
        {
            strcat(a->input, "11");
        }
        else if (!strcmp(found, "doce"))
        {
            strcat(a->input, "12");
        }
        else if (!strcmp(found, "trece"))
        {
            strcat(a->input, "13");
        }
        else if (!strcmp(found, "catorce"))
        {
            strcat(a->input, "14");
        }
        else if (!strcmp(found, "quince"))
        {
            strcat(a->input, "15");
        }
        else if (!strcmp(found, "dieciseis"))
        {
            strcat(a->input, "16");
        }
        else if (!strcmp(found, "diecisiete"))
        {
            strcat(a->input, "17");
        }
        else if (!strcmp(found, "dieciocho"))
        {
            strcat(a->input, "18");
        }
        else if (!strcmp(found, "diecinueve"))
        {
            strcat(a->input, "19");
        }
        else if (!strcmp(found, "veinte"))
        {
            strcat(a->input, "20");
        }
        else if (!strcmp(found, "veintiuno"))
        {
            strcat(a->input, "21");
        }
        else if (!strcmp(found, "veintidos"))
        {
            strcat(a->input, "22");
        }
        else if (!strcmp(found, "veintitres"))
        {
            strcat(a->input, "23");
        }
        else if (!strcmp(found, "veinticuatro"))
        {
            strcat(a->input, "24");
        }
        else if (!strcmp(found, "veinticinco"))
        {
            strcat(a->input, "25");
        }
        else if (!strcmp(found, "veintiseis"))
        {
            strcat(a->input, "26");
        }
        else if (!strcmp(found, "veintisiete"))
        {
            strcat(a->input, "27");
        }
        else if (!strcmp(found, "veintiocho"))
        {
            strcat(a->input, "28");
        }
        else if (!strcmp(found, "veintinueve"))
        {
            strcat(a->input, "29");
        }
        else if (!strcmp(found, "treinta"))
        {
            strcat(a->input, "30");
        }
        else if (!strcmp(found, "treintayuno"))
        {
            strcat(a->input, "31");
        }
        else if (!strcmp(found, "treintaydos"))
        {
            strcat(a->input, "32");
        }
        else if (!strcmp(found, "treintaytres"))
        {
            strcat(a->input, "33");
        }
        else if (!strcmp(found, "treintaycuatro"))
        {
            strcat(a->input, "34");
        }
        else if (!strcmp(found, "treintaycinco"))
        {
            strcat(a->input, "35");
        }
        else if (!strcmp(found, "treintayseis"))
        {
            strcat(a->input, "36");
        }
        else if (!strcmp(found, "treintaysiete"))
        {
            strcat(a->input, "37");
        }
        else if (!strcmp(found, "treintayocho"))
        {
            strcat(a->input, "38");
        }
        else if (!strcmp(found, "treintaynueve"))
        {
            strcat(a->input, "39");
        }
        else if (!strcmp(found, "cuarenta"))
        {
            strcat(a->input, "40");
        }
        else if (!strcmp(found, "cuarentayuno"))
        {
            strcat(a->input, "41");
        }
        else if (!strcmp(found, "cuarentaydos"))
        {
            strcat(a->input, "42");
        }
        else if (!strcmp(found, "cuarentaytres"))
        {
            strcat(a->input, "43");
        }
        else if (!strcmp(found, "cuarentaycuatro"))
        {
            strcat(a->input, "44");
        }
        else if (!strcmp(found, "cuarentaycinco"))
        {
            strcat(a->input, "45");
        }
        else if (!strcmp(found, "cuarentayseis"))
        {
            strcat(a->input, "46");
        }
        else if (!strcmp(found, "cuarentaysiete"))
        {
            strcat(a->input, "47");
        }
        else if (!strcmp(found, "cuarentayocho"))
        {
            strcat(a->input, "48");
        }
        else if (!strcmp(found, "cuarentaynueve"))
        {
            strcat(a->input, "49");
        }
        else if (!strcmp(found, "cincuenta"))
        {
            strcat(a->input, "50");
        }
        else if (!strcmp(found, "cincuentayuno"))
        {
            strcat(a->input, "51");
        }
        else if (!strcmp(found, "cincuentaydos"))
        {
            strcat(a->input, "52");
        }
        else if (!strcmp(found, "cincuentaytres"))
        {
            strcat(a->input, "53");
        }
        else if (!strcmp(found, "cincuentaycuatro"))
        {
            strcat(a->input, "54");
        }
        else if (!strcmp(found, "cincuentaycinco"))
        {
            strcat(a->input, "55");
        }
        else if (!strcmp(found, "cincuentayseis"))
        {
            strcat(a->input, "56");
        }
        else if (!strcmp(found, "cincuentaysiete"))
        {
            strcat(a->input, "57");
        }
        else if (!strcmp(found, "cincuentayocho"))
        {
            strcat(a->input, "58");
        }
        else if (!strcmp(found, "cincuentaynueve"))
        {
            strcat(a->input, "59");
        }
        else if (!strcmp(found, "sesenta"))
        {
            strcat(a->input, "60");
        }
        else if (!strcmp(found, "sesentayuno"))
        {
            strcat(a->input, "61");
        }
        else if (!strcmp(found, "sesentaydos"))
        {
            strcat(a->input, "62");
        }
        else if (!strcmp(found, "sesentaytres"))
        {
            strcat(a->input, "63");
        }
        else if (!strcmp(found, "sesentaycuatro"))
        {
            strcat(a->input, "64");
        }
        else if (!strcmp(found, "sesentaycinco"))
        {
            strcat(a->input, "65");
        }
        else if (!strcmp(found, "sesentayseis"))
        {
            strcat(a->input, "66");
        }
        else if (!strcmp(found, "sesentaysiete"))
        {
            strcat(a->input, "67");
        }
        else if (!strcmp(found, "sesentayocho"))
        {
            strcat(a->input, "68");
        }
        else if (!strcmp(found, "sesentaynueve"))
        {
            strcat(a->input, "69");
        }
        else if (!strcmp(found, "setenta"))
        {
            strcat(a->input, "70");
        }
        else if (!strcmp(found, "setentayuno"))
        {
            strcat(a->input, "71");
        }
        else if (!strcmp(found, "setentaydos"))
        {
            strcat(a->input, "72");
        }
        else if (!strcmp(found, "setentaytres"))
        {
            strcat(a->input, "73");
        }
        else if (!strcmp(found, "setentaycuatro"))
        {
            strcat(a->input, "74");
        }
        else if (!strcmp(found, "setentaycinco"))
        {
            strcat(a->input, "75");
        }
        else if (!strcmp(found, "setentayseis"))
        {
            strcat(a->input, "76");
        }
        else if (!strcmp(found, "setentaysiete"))
        {
            strcat(a->input, "77");
        }
        else if (!strcmp(found, "setentayocho"))
        {
            strcat(a->input, "78");
        }
        else if (!strcmp(found, "setentaynueve"))
        {
            strcat(a->input, "79");
        }
        else if (!strcmp(found, "ochenta"))
        {
            strcat(a->input, "80");
        }
        else if (!strcmp(found, "ochentayuno"))
        {
            strcat(a->input, "81");
        }
        else if (!strcmp(found, "ochentaydos"))
        {
            strcat(a->input, "82");
        }
        else if (!strcmp(found, "ochentaytres"))
        {
            strcat(a->input, "83");
        }
        else if (!strcmp(found, "ochentaycuatro"))
        {
            strcat(a->input, "84");
        }
        else if (!strcmp(found, "ochentaycinco"))
        {
            strcat(a->input, "85");
        }
        else if (!strcmp(found, "ochentayseis"))
        {
            strcat(a->input, "86");
        }
        else if (!strcmp(found, "ochentaysiete"))
        {
            strcat(a->input, "87");
        }
        else if (!strcmp(found, "ochentayocho"))
        {
            strcat(a->input, "88");
        }
        else if (!strcmp(found, "ochentaynueve"))
        {
            strcat(a->input, "89");
        }
        else if (!strcmp(found, "noventa"))
        {
            strcat(a->input, "90");
        }
        else if (!strcmp(found, "noventayuno"))
        {
            strcat(a->input, "91");
        }
        else if (!strcmp(found, "noventaydos"))
        {
            strcat(a->input, "92");
        }
        else if (!strcmp(found, "noventaytres"))
        {
            strcat(a->input, "93");
        }
        else if (!strcmp(found, "noventaycuatro"))
        {
            strcat(a->input, "94");
        }
        else if (!strcmp(found, "noventaycinco"))
        {
            strcat(a->input, "95");
        }
        else if (!strcmp(found, "noventayseis"))
        {
            strcat(a->input, "96");
        }
        else if (!strcmp(found, "noventaysiete"))
        {
            strcat(a->input, "97");
        }
        else if (!strcmp(found, "noventayocho"))
        {
            strcat(a->input, "98");
        }
        else if (!strcmp(found, "noventaynueve"))
        {
            strcat(a->input, "99");
        }
        else if (!strcmp(found, "cien"))
        {
            strcat(a->input, "100");
        }
        found = strtok(NULL, ",");
    }
    if (strlen(a->input) != 9)
    {
        printf("El número introducido no es de 9 digitos.\n");
    }
    else
    {
        printf("Tu ID introducido es: %s\n", a->ID);
        shiftString(a->input, 4);
        printf("Muchas gracias, el nuevo ID es: ");

        for (int i = 0; i < strlen(a->ID); i++)
        {
            printf("%c", a->ID[i]);
        }

        printf("\n");
    }

    return 0;
}

char *shiftString(char *str, int shiftBy)
{
    char *buff = malloc((sizeof(char) * shiftBy) + 1);
    int i = 0;

    strncpy(buff, str, shiftBy);

    buff[shiftBy] = '\0';

    while (str[i + shiftBy] != '\0')
    {
        str[i] = str[i + shiftBy];
        str[i + shiftBy] = '\0';
        i++;
    }

    strcat(str, buff);

    return str;
}

void deleteBlankSpaces(char *s)
{
    int i, aux = 0;

    for (i = 0; s[i]; i++)
    {
        s[i] = s[i + aux];

        if (s[i] == ' ' || s[i] == '\t')
        {
            aux++;
            i--;
        }
    }
}