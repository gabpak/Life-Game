/*
    Authors: 
        Gabin PAQUES,
        Marin DUDOUET,
        Julia SERPE.

    Created at: 19-09-2023

    Last modification at: 17-10-2023

    Version: 2.0.1

    Description: 
        Game life project for the ECE Paris course "Programmation C".
    
    Compilation:
        debug:      gcc main.c -o main -Wall -Werror -pedantic
        release:    gcc main.c -o main -Wall -Werror -Wextra -pedantic -O3
    
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
#include <windows.h> // Sleep function for Windows

#define MAP_SIZE 30 // /!\ MAKE SURE THE .lvl FILE IS THE SAME SIZE /!\ //
#define MAX_GENERATION 20
#define DEAD 0
#define ALIVE 1
#define SLEEP_TIME 250 // Milliseconds

FILE *file = NULL;

// ~~~~~~~~~~~~~~~~~~~~~~~ Init ~~~~~~~~~~~~~~~~~~~~~~~ //
typedef enum {false, true} bool;
int currentGeneration = 0;

// ~~~~~~~~~~~~~~~~~~~~~~~ Functions Prototypes ~~~~~~~~~~~~~~~~~~~~~~~ //
void wait(int ms); // Function to wait (in ms) because sleep() is in seconds.
void initMap(int map[][MAP_SIZE]);
void updateMap(int map[][MAP_SIZE]);
void drawMap(int map[][MAP_SIZE]);
void readLevel(int map[][MAP_SIZE]);

// ~~~~~~~~~~~~~~~~~~~~~~~ Main ~~~~~~~~~~~~~~~~~~~~~~~ //
int main(){
    int map[MAP_SIZE][MAP_SIZE];
    initMap(map); // Init the map

    file = fopen("cells.lvl", "r"); // Open the file
    if(file == NULL){
        printf("\nERROR: main() function => file variable is null\n");
        exit(1);
    }

    readLevel(map); // Read the file

    while(currentGeneration < MAX_GENERATION){
        currentGeneration++;
        drawMap(map);
        updateMap(map);
        wait(SLEEP_TIME);
    }

    return 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~ Functions Definitions ~~~~~~~~~~~~~~~~~~~~~~~ //
void wait(int time){
    Sleep(time);
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
    system("cls");
    printf("\nGen: %i / %i \n", currentGeneration, MAX_GENERATION);

    for(int i = 0; i < MAP_SIZE; ++i){
        for(int j = 0; j < MAP_SIZE; ++j){
            if(map[i][j] == DEAD){
                printf(". "); 
            }
            else if(map[i][j] == ALIVE){
                printf("%c ", 254u); // 254u is the code for the character "█"
            }
            else{
                printf("\nWARNING: drawmap() function => map value is neither ALIVE or DEAD\n");
                printf("%c ", 146u); // Random character to show that there is a problem
            }

        }
        printf("\n");
    }
}

void readLevel(int map[][MAP_SIZE]){
    if(file == NULL){
        printf("\nERROR: readLevel() function => file variable is null\n");
        exit(1);
    }
    
    char c = ' ';
    for(int i = 0; i < MAP_SIZE; ++i){
        for(int j = 0; j < MAP_SIZE + 1; j++){
            c = fgetc(file);
            if(c != '\n'){
                if(c == '1'){
                    map[i][j] = ALIVE;
                }
                else if(c == '0'){
                    map[i][j] = DEAD;
                }
                else if(c == EOF){
                    break;
                }
            }
        }
    }
}