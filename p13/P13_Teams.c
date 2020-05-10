// Marcos Leroy Salazar Skinner
// A01039743
// Moisés Fernández Zárate
// A01197049
// Date: 25/4/2020

// Practice 13
// Dynamic Windows Libraries
// Programa en el que usamos un dll compilado para usar sus funciones

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

HINSTANCE hDll; //Apuntador a la libreria dll

typedef int (ASCIITOBINARY)(char* s);
typedef int (ASCIITOHEX)(char* s);
typedef double (ASCIITODOUBLE)(char* s);

ASCIITOBINARY* pfuncAsciiBinaryToInt = 0;
ASCIITOHEX* pfuncAsciiHEXToInt = 0;
ASCIITODOUBLE* pfuncAsciiToDouble = 0;

int main() {
    int iOption, iConversion;
    char sBinary[32], sHEX[8], sAscii[10];
    double dConversion;

    if (hDll = LoadLibrary("theDll.dll")) {
        pfuncAsciiBinaryToInt = (ASCIITOBINARY*) GetProcAddress(hDll, "asciiBinaryToInt");
        pfuncAsciiHEXToInt = (ASCIITOHEX*) GetProcAddress(hDll, "asciiHEXToInt");
        pfuncAsciiToDouble = (ASCIITODOUBLE*) GetProcAddress(hDll, "asciiToDouble");

        if (!pfuncAsciiBinaryToInt || !pfuncAsciiHEXToInt || !pfuncAsciiToDouble) {
            printf("Functions not found correctly!\n");
            FreeLibrary(hDll);
            return 0;
        }
        else {
            // Menu para decidir que conversion usar
            do {
                printf("\nHello agent, select what you want to convert\n");
                printf("1.- Binary -> Int\n");
                printf("2.- Hexadecimal -> Int\n");
                printf("3.- ASCII -> Double\n");
                printf("0.- Exit...\n\n");
                printf("Pick an option: ");

                scanf("%d", &iOption);

                switch (iOption) {
                case 1:
                    printf("Type the Binary string: ");
                    scanf("%s", sBinary);

                    iConversion = pfuncAsciiBinaryToInt(sBinary);
                    printf("\nThe conversion from Binary is: %d\n", iConversion);

                    break;

                case 2:
                    printf("Type the Hexadecimal string: ");
                    scanf("%s", sHEX);

                    iConversion = pfuncAsciiHEXToInt(sHEX);
                    printf("\nThe conversion from Hexadecimal is: %d\n", iConversion);

                    break;

                case 3:
                    printf("Type the ASCII string: ");
                    scanf("%s", sAscii);

                    dConversion = pfuncAsciiToDouble(sAscii);
                    printf("\nThe conversion from Ascii is: %lf\n", dConversion);

                    break;

                case 0:
                    printf("Thank you agent, now all info will be destroyed...\n");
                    break;

                default:
                    printf("Invalid option, try again...\n");
                    break;
                }
            } while (iOption != 0);
        }

    } else
        printf("Library not found!\n");

    FreeLibrary(hDll);

    return 0;
}
