/*
*   Author: Moisés Fernández Zárate A01197049
*   Date created: 13/03/2020
*
*   Convert.c
*   In this homework we practice with pointers, arrays, strings and streams.
*/
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
*   Function: int asciiBinaryToInt(char *s)
*   This function converts a binary number received as a string
*	into a decimal number.
*   Parameters: char *s, the binary number that will be converted to int.
*   Return value: an integer that is the conversion of the binary number.
*/
int asciiBinaryToInt(char *s);

/*
*   Function: int asciiHEXToInt(char *s)
*   This function converts a hexadecimal number received as a string
*	into a decimal number.
*   Parameters: char *s, the hexadecimal number that will be converted to int.
*   Return value: an integer that is the conversion of the hexadecimal number.
*/
int asciiHEXToInt(char *s);

/*
*   Function: int asciiToDouble(char *s)
*   This function converts a double received as a string into a double number.
*   Parameters: char *s, the double as a string that will be converted to double.
*   Return value: a double number that is the conversion of the string.
*/
double asciiToDouble(char *s);

int main(void) {
	char *s;
	int iResult;
	double dResult;

	// Binary conversion.
	printf("Please enter a binary number: ");
	scanf("%s", s);
	iResult = asciiBinaryToInt(s);

	while (iResult == -1)
	{
		printf("Please enter a valid binary number: ");
		scanf("%s", s);
		iResult = asciiBinaryToInt(s);
	}

	printf("The conversion to decimal from %s is %d.\n", s, iResult);

	// Hexadecimal conversion.
	printf("Please enter a hexadecimal number: ");
	scanf("%s", s);
	iResult = asciiHEXToInt(s);

	while (iResult == -1)
	{
		printf("Please enter a valid hexadecimal number: ");
		scanf("%s", s);
		iResult = asciiHEXToInt(s);
	}

	printf("The conversion to decimal from %s is %d.\n", s, iResult);

	// Double conversion.
	printf("Please enter the double number: ");
	scanf("%s", s);
	dResult = asciiToDouble(s);
	printf("The conversion to double from %s is %lf.\n", s, dResult);

	return 0;
}

int asciiBinaryToInt(char *s) 
{
	int conversion = 0;
	int multiplier = 1;

	for (int i = strlen(s) - 1; i >= 0; i--) 
	{
		if (s[i] == '1')
		{
			conversion += multiplier;
		}
		else if (s[i] != '0')
		{
			return -1;
		}

		multiplier *= 2;
	}

	return conversion;
}

int asciiHEXToInt(char *s)
{
	int conversion = 0;
	int hexConverted = 0;
	long unsigned exponent;

	for (int i = 0; i < strlen(s); i++)
	{
		exponent = strlen(s) - i - 1;

		if (s[i] >= '0' && s[i] <= '9')
        {
            hexConverted = s[i] - '0';
        }
        else if (s[i] >= 'a' && s[i] <= 'f')
        {
            hexConverted = s[i] - 'a' + 10;
        }
        else if (s[i]>='A' && s[i] <= 'F')
        {
            hexConverted = s[i] - 'A' + 10;
        }
		else 
		{
			return -1;
		}

		conversion += hexConverted * pow(16, exponent);
	}

	return conversion;
}

double asciiToDouble(char *s)
{
	int i = 0;
    double sign = 1.0;
    double conversion = 0.0;
	double exponent = 1.0;

    if (s[i] == '+' || s[i] == '-')
	{
        if (s[i] == '+')
		{
            i++;
        }
        else 
		{
            sign *= -1;

            i++;
        }
    }

    while (s[i] >= '0' && s[i] <= '9') 
	{
        conversion = conversion * 10.0 + (s[i] - '0');

        i++;
    }

    if (s[i] == '.')
	{
        i++;
    }

    while(s[i] >= '0' && s[i] <= '9') 
	{
        conversion += (s[i] - '0') / (10.0 * exponent);
        exponent *= 10.0;
        i++;
    }

    return conversion * sign;
}