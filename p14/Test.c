// Marcos Leroy Salazar Skinner
// A01039743
// Moisés Fernández Zárate
// A01197049
// Date: 10/5/2020
#include <stdio.h>
#include <math.h>
#include "Convert.h"

int main() {
    char *binaryNumber = "11111111";
    char *hexNumber = "A2F7";
    char *doubleNumber = "162.351";
    int iResult;
    double dResult;

    iResult = asciiBinaryToInt(binaryNumber);
    printf("The conversion to integer from %s is %d.\n", binaryNumber, iResult);
    iResult = asciiHEXToInt(hexNumber);
    printf("The conversion to integer from %s is %d.\n", hexNumber, iResult);
    dResult = asciiToDouble(doubleNumber);
    printf("The conversion to double from %s is %lf.\n", doubleNumber, dResult);
}