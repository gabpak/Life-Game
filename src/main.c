/*
    Authors: 
        Gabin PAQUES,
        Marin DUDOUET,
        Julia SERPE.

    Created at: 19-09-2023

    Version: 0.0.1

    Description: 
        Game life project game in C.
    
    Compilation:
        gcc -o main main.c -Wall -Wextra -Werror
    
    Execution:
        ./main
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // Sleep function

#define MAP_SIZE 10
#define DEAD 0
#define ALIVE 1
#define SLEEP_TIME 250 // In ms

// ~~~~~~~~~~~~~~~~~~~~~~~ Init ~~~~~~~~~~~~~~~~~~~~~~~ //
typedef enum {false, true} bool;

// ~~~~~~~~~~~~~~~~~~~~~~~ Functions Prototypes ~~~~~~~~~~~~~~~~~~~~~~~ //
void wait(int ms); // Function to wait (in ms) because sleep() is in seconds.
void initMap(int map[][MAP_SIZE]);
void updateMap(int map[][MAP_SIZE]);
void drawMap(int map[][MAP_SIZE]);

// ~~~~~~~~~~~~~~~~~~~~~~~ Main ~~~~~~~~~~~~~~~~~~~~~~~ //
int main(){
    bool isRunning = true;
    int map[][MAP_SIZE] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 3, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},};
    //initMap(map);

    while(isRunning){
        //TODO: Game loop
        updateMap(map);
        drawMap(map);
        wait(SLEEP_TIME);
        break;
    }

    return 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~ Functions Definitions ~~~~~~~~~~~~~~~~~~~~~~~ //
void wait(int ms){
    sleep(ms / 1000);
}

void initMap(int map[][MAP_SIZE]){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            map[i][j] = DEAD;
        }
    }
}

void updateMap(int map[][MAP_SIZE]){
    // TODO
}

void drawMap(int map[][MAP_SIZE]){
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