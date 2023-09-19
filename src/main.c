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

#define MAP_SIZE 10

// ~~~~~~~~~~~~~~~~~~~~~~~ Functions Prototypes ~~~~~~~~~~~~~~~~~~~~~~~ //
void initMap(int map[][MAP_SIZE]);
void drawMap(int map[][MAP_SIZE]);

// ~~~~~~~~~~~~~~~~~~~~~~~ Init ~~~~~~~~~~~~~~~~~~~~~~~ //
typedef enum {false, true} bool;

// ~~~~~~~~~~~~~~~~~~~~~~~ Main ~~~~~~~~~~~~~~~~~~~~~~~ //
int main(){
    bool isRunning = true;
    int map[][MAP_SIZE] = { {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},};
    initMap(map);

    while(isRunning){
        //TODO: Game loop
        drawMap(map);
        break;
    }

    return 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~ Functions Definitions ~~~~~~~~~~~~~~~~~~~~~~~ //
void initMap(int map[][MAP_SIZE]){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            map[i][j] = 0;
        }
    }
}

void drawMap(int map[][MAP_SIZE]){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            if(map[i][j] == 0){
                printf(". ");
            }
            else{
                printf("%c ", 254u);
            }

        }
        printf("\n");
    }
}