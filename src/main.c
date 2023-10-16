/*
    Authors: 
        Gabin PAQUES,
        Marin DUDOUET,
        Julia SERPE.

    Created at: 19-09-2023

    Last modification at: 16-10-2023

    Version: 1.0.2

    Description: 
        Game life project for the ECE Paris course "Programmation C".
    
    Compilation:
        debug:      gcc main.c -o main -Wall -Werror
        release:    gcc main.c -o main -Wall -Werror -Wextra -O3
    
    Execution:
        ./main

    Sources:
        https://cypris.fr/loisirs/le_jeu_de_la_vie.pdf
        https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
        https://conwaylife.com/wiki/Main_Page
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // Sleep function

#define MAP_SIZE 30 // Size of the map x * x
#define DEAD 0
#define ALIVE 1
#define SLEEP_TIME 500 // Milliseconds

FILE *file = NULL;

// ~~~~~~~~~~~~~~~~~~~~~~~ Init ~~~~~~~~~~~~~~~~~~~~~~~ //
typedef enum {false, true} bool;
int generation = 0;
int generationMax = 20;

// ~~~~~~~~~~~~~~~~~~~~~~~ Functions Prototypes ~~~~~~~~~~~~~~~~~~~~~~~ //
void wait(int ms); // Function to wait (in ms) because sleep() is in seconds.
void initMap(int map[][MAP_SIZE]);
void updateMap(int map[][MAP_SIZE]);
void drawMap(int map[][MAP_SIZE]);
void askCoord(int map[][MAP_SIZE]);
void readLevel(int map[][MAP_SIZE]);

// ~~~~~~~~~~~~~~~~~~~~~~~ Main ~~~~~~~~~~~~~~~~~~~~~~~ //
int main(){
    int map[MAP_SIZE][MAP_SIZE];
    initMap(map); // Init the map

    //askCoord(map); // Asking the points to add on the map
    file = fopen("cells.lvl", "r"); // Open the file
    readLevel(map); // Read the file

    while(generation < generationMax){
        generation++;
        drawMap(map);
        updateMap(map);
        wait(SLEEP_TIME);
    }

    return 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~ Functions Definitions ~~~~~~~~~~~~~~~~~~~~~~~ //
void wait(int time){
    usleep(time * 1000); // usleep() is in microseconds so we multiply by 1000 to have milliseconds
}

void initMap(int map[][MAP_SIZE]){
    for(int i = 0; i < MAP_SIZE; ++i){
        for(int j = 0; j < MAP_SIZE; ++j){
            map[i][j] = DEAD;
        }
    }
}

void updateMap(int map[][MAP_SIZE]){

    int newMap[MAP_SIZE][MAP_SIZE]; // We create a new map to not modify the current one
    initMap(newMap);

    for(int i = 0; i < MAP_SIZE; ++i){
        for(int j = 0; j < MAP_SIZE; ++j){
            int countNeighbour = 0;

            // We count the number of neighbours
            if((i > 0) && (map[i - 1][j] == ALIVE)){ // Left cell
                countNeighbour++;
            }
            if((i > 0) && (j > 0) && (map[i - 1][j - 1] == ALIVE)){ // Top Left cell
                countNeighbour++;
            }
            if((j > 0) && (map[i][j - 1] == ALIVE)){ // Top cell
                countNeighbour++;
            }
            if((j > 0) && (i < MAP_SIZE - 1) && (map[i + 1][j - 1] == ALIVE)){ // Top Right cell
                countNeighbour++;
            }

            if((i < (MAP_SIZE - 1)) && (map[i + 1][j] == ALIVE)){ // Right cell
                countNeighbour++;
            }
            if((i < (MAP_SIZE - 1)) && (j < (MAP_SIZE - 1)) && (map[i + 1][j + 1] == ALIVE)){ // Bottom Right cell
                countNeighbour++;
            }
            if((j < (MAP_SIZE - 1)) && (map[i][j + 1] == ALIVE)){ // Bottom cell
                countNeighbour++;
            }
            if((i < (MAP_SIZE - 1)) && (j < (MAP_SIZE - 1)) && map[i - 1][j + 1] == ALIVE){ // Bottom Left cell
                countNeighbour++;
            }

            // /*\ /*\ /*\ /*\ RULES /*\ /*\ /*\ /*\ //

            if(map[i][j] == ALIVE){
                if(countNeighbour < 2 || countNeighbour > 3){
                    newMap[i][j] = DEAD; // Die because of underpopulation or overpopulation
                }
                else{
                    newMap[i][j] = ALIVE; // Survive
                }
            }
            else{
                if(countNeighbour == 3){
                    newMap[i][j] = ALIVE; // Become alive because of reproduction
                }
                else{
                    newMap[i][j] = DEAD; // Stay dead
                }
            }
        }
    }

    // Copy of newMap into map
    for(int i = 0; i < MAP_SIZE; ++i){
        for(int j = 0; j < MAP_SIZE; ++j){
            map[i][j] = newMap[i][j];
        }
    }
}

void drawMap(int map[][MAP_SIZE]){
    if(generation != 0){
        printf("\nGen: %i / %i \n", generation, generationMax);
    }

    for(int i = 0; i < MAP_SIZE; ++i){
        for(int j = 0; j < MAP_SIZE; ++j){
            if(map[i][j] == DEAD){
                printf(". "); 
            }
            else if(map[i][j] == ALIVE){
                printf("%c ", 254u); // 254u is the code for the character "█"
            }
            else{
                printf("%c ", 146u); // Random character to show that there is a problem
            }

        }
        printf("\n");
    }
}

void readLevel(int map[][MAP_SIZE]){
    if(file == NULL){
        printf("\nError: The file is NULL.\n");
        exit(1);
    }

    char c = ' ';
    for(int i = 0; i < MAP_SIZE + 1; ++i){
        for(int j = 0; j < MAP_SIZE + 1; j++){
            c = fgetc(file);
            if(c != '\n'){
                if(c == '1'){
                    map[i][j] = ALIVE;
                }
                else if(c == '0'){
                    map[i][j] = DEAD;
                }
            }
        }
    }
    
    // Check for extra characters after the expected data
    int extraChar = fgetc(file);
    if (extraChar != EOF && extraChar != '\n') {
        printf("\nError: Extra characters in the file.\n");
        exit(1);
    }
}

void askCoord(int map[][MAP_SIZE]){
    printf("\nHow many points do you want to enter?: ");
    int nbPoints = 0;
    scanf("%i", &nbPoints);

    if(nbPoints > (MAP_SIZE * MAP_SIZE)){
        printf("\nError: You can't enter more than %i points.\n", MAP_SIZE * MAP_SIZE);
        exit(1);
    }
    if(nbPoints < 0){
        printf("\nError: You can't enter less than 0 points.\n");
        exit(1);
    }
    if(nbPoints == 0){
        printf("\nError: You can't enter 0 points.\n");
        exit(1);
    }

    printf("\nEnter the coordinates of the cells between 0 and %i: \n ", MAP_SIZE - 1);
    int x, y = 0;

    for(int i = 0; i < nbPoints; ++i){
        printf("\nX = ");
        scanf("%i", &y);
        if(y > MAP_SIZE - 1){
            printf("\nError: You can't enter a number greater than %i.\n", MAP_SIZE - 1);
            exit(1);
        }
        if(y < 0){
            printf("\nError: You can't enter a number less than 0.\n");
            exit(1);
        }

        printf("\nY = ");
        scanf("%i", &x);
        if(x > MAP_SIZE - 1){
            printf("\nError: You can't enter a number greater than %i.\n", MAP_SIZE - 1);
            exit(1);
        }
        if(x < 0){
            printf("\nError: You can't enter a number less than 0.\n");
            exit(1);
        }

        map[x][y] = ALIVE;

        drawMap(map);
    }

    // Ask for the number of generations
    printf("\nHow many generations do you want to see?: ");
    scanf("%i", &generationMax);
    if(generationMax <= 0){
        printf("\nError: You can't enter a number less than 0.\n");
        exit(1);
    }
}