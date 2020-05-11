// Moisés Fernández Zárate A01197049
// Hour Of Code 3
// 28/04/2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct to store a coordinate with its latitude and longitude.
typedef struct Coord {
    char cLat[100];
    double dLat;
    char cLong[100];
    double dLong;
} Coord;

/*
*   Function to store the coordinates and sort them in ascending order.
*   Parameters: file, the file from where the coordinates are read.
*               coordinatesList, the list where the coordinates will be stored.
*               numberCoordinates, the number coordinates in the file.
*   Return value: None.
*/
void storeCoordinates(FILE *file, Coord* coordinatesList, int numberCoordinates);

/*
*   Function to compare two coordinates' values (latitude and longitude) and
*   it is used to sort the list of coordinates.
*   Parameters: c1, one coordinate that will be compared.
*               c2, the other coordinate that will be compared with c1.
*   Return value: an integer that means which one is smaller.
*/
int compare(const void * c1, const void * c2);

/*
*   Function to change the characters for cardinal points to words.
*   Parameters: cardinal, the character that will be changed to a word.
*   Return value: a string, the word to which the character was changed.
*/
char* changeCardinals(const char cardinal);

/*
*   Function to search for the characters of the cardinals in a coordinate.
*   Parameters: the coordinate to search in for the character of the cardinal.
*   Return value: None.
*/
void searchCardinals(char coordinate[]);

/*
*   Function to generate the new files.
*   Parameters: coordinatesList, to send the information to the files.
*               numberCoordinates, the number of coordinates in the list.
*   Return value: None.
*/
void generateFiles(Coord *coordinatesList, int numberCoordinates);

// Main function.
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s (name of the file)\n", argv[0]);
        exit(1);
    }

    // Get the name of the file and store it with the var type FILE.
    char *nameFile = argv[1];
    FILE *file = fopen(nameFile, "r");

    // To store the number of coordinates that the file has.
    char input[300];
    int numberCoordinates = 0;

    while (fscanf(file, "%s", input) == 1)
    {
        numberCoordinates++;
    }

    rewind(file);

    // Divide by 6 because of the coordinate format:
    // Latitude: a b
    // Longitude: c d
    numberCoordinates /= 6;

    Coord* coordinatesList = (Coord *) malloc(sizeof(Coord)*numberCoordinates);

    storeCoordinates(file, coordinatesList, numberCoordinates);

    generateFiles(coordinatesList, numberCoordinates);

    fclose(file);
    free(coordinatesList);
}

void storeCoordinates(FILE *file, Coord* coordinatesList, int numberCoordinates)
{
    char cLong[50];
    double dLong;
    char cLat[50];
    double dLat;

    char temp[50];

    for (int i = 0; i < numberCoordinates; i++)
    {
        fscanf(file, "%s", temp);
        fscanf(file, "%s", cLat);
        fscanf(file, "%lf", &dLat);
        fscanf(file, "%s", temp);
        fscanf(file, "%s", cLong);
        fscanf(file, "%lf", &dLong);

        Coord coordinate;

        strcpy(coordinate.cLat, cLat);
        strcpy(coordinate.cLong, cLong);

        coordinate.dLat = dLat;
        coordinate.dLong = dLong;

        coordinatesList[i] = coordinate;
    }    
    
    rewind(file);

    qsort(coordinatesList, numberCoordinates, sizeof(Coord), compare);
}

int compare(const void * c1, const void * c2) {
    struct Coord *coord1 = (struct Coord *)c1;
    struct Coord *coord2 = (struct Coord *)c2;

    if (coord1->dLat < coord2->dLat) {
        return -1;
    }
    else if(coord1->dLat > coord2->dLat) {
        return 1;
    }
    else if(coord1->dLong < coord2->dLong) {
        return -1;
    }
    else if(coord1->dLong > coord2->dLong) {
        return 1;
    }

    return 0;
}

char* changeCardinals(const char cardinal)
{
    if (cardinal == 'N') {
        return "North";
    }
    if (cardinal == 'E') {
        return "East";
    }
    if (cardinal == 'S') {
        return "South";
    }
    if (cardinal == 'W') {
        return "West";
    }
}

void searchCardinals(char coordinate[])
{
    char *quote = strstr(coordinate, "″");
    strcpy(quote + 3, changeCardinals(*(quote + 3)));
}

void generateFiles(Coord *coordinatesList, int numberCoordinates)
{
    FILE *file1 = fopen("file1.txt", "w");
    FILE *file2 = fopen("file2.txt", "w");

    for (int i = 0; i < numberCoordinates; i++)
    {
        searchCardinals(coordinatesList[i].cLat);
        searchCardinals(coordinatesList[i].cLong);

        fprintf(file1, "%s %s\n", coordinatesList[i].cLat, coordinatesList[i].cLong);
        fprintf(file2, "%lf %lf\n", coordinatesList[i].dLat, coordinatesList[i].dLong);
    } 

    fclose(file1);
    fclose(file2);
}