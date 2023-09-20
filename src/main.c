/*
    Authors: 
        Gabin PAQUES,
        Marin DUDOUET,
        Julia SERPE.

    Created at: 19-09-2023

    Last modification at: 20-09-2023

    Version: 0.1.0

    Description: 
        Game life project game in C.
    
    Compilation:
        debug:      gcc main.c -o main -Wall -Werror
        release:    gcc main.c -o main -Wall -Werror -Wextra
    
    Execution:
        ./main
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // Sleep function

#define MAP_SIZE 20
#define DEAD 0
#define ALIVE 1
#define SLEEP_TIME 1
#define GENERATION_MAX 5

// ~~~~~~~~~~~~~~~~~~~~~~~ Init ~~~~~~~~~~~~~~~~~~~~~~~ //
typedef enum {false, true} bool;
int generation = 0;

// ~~~~~~~~~~~~~~~~~~~~~~~ Functions Prototypes ~~~~~~~~~~~~~~~~~~~~~~~ //
void wait(int ms); // Function to wait (in ms) because sleep() is in seconds.
void initMap(int map[][MAP_SIZE]);
void updateMap(int map[][MAP_SIZE]);
void drawMap(int map[][MAP_SIZE]);

// ~~~~~~~~~~~~~~~~~~~~~~~ Main ~~~~~~~~~~~~~~~~~~~~~~~ //
int main(){
    bool isRunning = true;
    int map[MAP_SIZE][MAP_SIZE];
    initMap(map);

    while(isRunning && generation < GENERATION_MAX){
        generation++;
        drawMap(map);
        updateMap(map);
        wait(SLEEP_TIME);
    }

    return 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~ Functions Definitions ~~~~~~~~~~~~~~~~~~~~~~~ //
void wait(int time){
    sleep(time);
}

void initMap(int map[][MAP_SIZE]){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            map[i][j] = DEAD;
        }
    }
}

void updateMap(int map[][MAP_SIZE]){

    int newMap[MAP_SIZE][MAP_SIZE]; // We create a new map to not modify the current one
    initMap(newMap);

    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            int countNeighbour = 0;

            // We count the number of neighbour
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

            // Born
            if( (map[i][j] == DEAD) && (countNeighbour == 3) ){ 
                newMap[i][j] = ALIVE;
            }
            // Survive
            if( (map[i][j] == ALIVE) && ((countNeighbour == 2) || (countNeighbour == 3)) ){ 
                newMap[i][j] = ALIVE; // Stay alive
            }
            // Death by isolation
            if( (map[i][j] == ALIVE) && ((countNeighbour == 0) || (countNeighbour == 1))){
                newMap[i][j] = DEAD;
            }
            // Death by surpopulation
            if( (map[i][j] == ALIVE) && (countNeighbour >= 3)){
                newMap[i][j] = DEAD;
            }
        }
    }

    // Copy of newMap into map
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            map[i][j] = newMap[i][j];
        }
    }
}

void drawMap(int map[][MAP_SIZE]){
    printf("\nGen: %i / %i \n", generation, GENERATION_MAX);
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
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