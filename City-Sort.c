/*
ECE 103
Homework #6
Benjamin.Warren
Program Description: Program takes input file containing cities and population size, stores dynamically as a n array of structs,
then prints out the array of structs sorted by either population or name.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char name[100];
    int population;
} city;

//Function to sort array of structs by population
int int_sort (const void * a, const void * b) {
   return (((city*)a)->population - ((city*)b)->population);
}

//Function to sort array of structs by name
int str_sort (const void* c, const void* d) {
    return strcmp(((city*)c)->name, ((city*)d)->name);
}

//Dynamically allocates array of structs
int allocArray (FILE *in_file, city **cities) {
    int i = 0;
    char chr;

    chr = getc(in_file);
    while (chr != EOF){
        if (chr == 10) {
            i = i + 1;
        }
        chr = getc(in_file);
    }
    *cities = calloc(i, (i - 1)*sizeof(cities));
    fseek(in_file, 0, SEEK_SET);
    return i;
}

//Populates array of structures with names of cities and population size
void popArray(int cityCount, FILE *in_file, city*cities) {
    for(int i = 0; i < cityCount; ++i) {
        fscanf(in_file, "%[^,]s", cities[i].name);
        fscanf(in_file, ",%d", &cities[i].population);
    }
}

//nameSort takes in file info and makes a list sorted by name of city
void nameSort(city *cities, int cityCount) {
    printf("\nSorted list by name:\n\n");
    qsort(cities, cityCount, sizeof(city), str_sort);
    for(int i = 0; i <= cityCount; ++i) {
        printf("%s,%d", cities[i].name, cities[i].population);
    }
}

//populationSort takes in file info and makes a list sorted by population of city
void populationSort(city *cities, int cityCount) {
    printf("\nSorted list by population:\n\n");
    qsort(cities, cityCount, sizeof(city), int_sort);
    for(int i = 0; i <= cityCount; ++i) {
        printf("%s,%d", cities[i].name, cities[i].population);
    }
}

//fileRead takes in the file specified and sorts the information
bool Sel(char select, city *cities, int cityCount) {
    if(select == 'N'|| select == 'n') {
        printf("Sorting by name\n");
        nameSort(cities, cityCount);
    }
    else if(select == 'P' || select == 'p') {
        printf("Sorting by population\n");
        populationSort(cities, cityCount);
    }
    else if(select == 'Q' || select == 'q'){
        printf("\nProgram done\n");
        return false;
    }
    else {
        printf("\nUnknown choice. Try again\n");
    }
    return true;
}

//Start and stop of program
int main(int argc, char *argv[]) {
    bool loop = true;
    char select[100];
    int rowCount;
    FILE *in_file = fopen(argv[1], "r");

    city *cities;
    rowCount = allocArray(in_file, &cities);
    popArray(rowCount, in_file, cities);

    if(argc == 1) {
        printf("\nERROR: Input filename is missing\n");
        return -1;
    }
    else {
        if (in_file == NULL) {
            printf("\nERROR: cannot open input file\n");
            return -1;
        }
        else {
            do {
                printf("\nOptions :\n");
                printf("    [N] Sort by name\n");
                printf("    [P] Sort by population\n");
                printf("    [Q] Quit\n\n");

                printf("Enter your choice: ");
                fgets(select, 100, stdin);

                loop = Sel(select[0], cities, rowCount);
            } while(loop == true);
        }
    }

    for (int i = 0; i < rowCount; i++) {
        free(cities[i].name);
        free(&cities[i].population);
    }
    free(cities);

    return 0;
}
