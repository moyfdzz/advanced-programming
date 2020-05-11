#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Convert.h"

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