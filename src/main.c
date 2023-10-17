/*
    Authors: 
        Gabin PAQUES,
        Marin DUDOUET,
        Julia SERPE.

    Created at: 19-09-2023

    Last modification at: 17-10-2023

    Version: 3.1.0

    Description: 
        Game life project for the ECE Paris course "Programmation C". Implementation of the graphics with the PDCurses library.
    
    Compilation (PDCurse):
        debug:      gcc  main.c -o main "pdcurses.a" -Wall -Werror -pedantic
        release:    gcc  main.c -o main "pdcurses.a" -Wall -Werror -Wextra -pedantic -O3

    Execution:
        ./main

    Sources:
        https://cypris.fr/loisirs/le_jeu_de_la_vie.pdf
        https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
        https://conwaylife.com/wiki/Main_Page
*/

#include <unistd.h> // Sleep function
#include "curses.h"

#define MAP_SIZE 40 // /!\ MAKE SURE THE .lvl FILE IS THE SAME SIZE /!\ //
#define DEAD 0
#define ALIVE 1
#define SLEEP_TIME 10 // Milliseconds

FILE *file = NULL;

// ~~~~~~~~~~~~~~~~~~~~~~~ Init ~~~~~~~~~~~~~~~~~~~~~~~ //
int currentGeneration = 0;

// ~~~~~~~~~~~~~~~~~~~~~~~ Functions Prototypes ~~~~~~~~~~~~~~~~~~~~~~~ //
void initMap(int map[][MAP_SIZE]);
void updateMap(int map[][MAP_SIZE]);
void drawMap(int map[][MAP_SIZE]);
void readLevel(int map[][MAP_SIZE]);
void drawBorder();

// ~~~~~~~~~~~~~~~~~~~~~~~ Main ~~~~~~~~~~~~~~~~~~~~~~~ //
int main(){

    // Init the terminal with PDcurses
    initscr(); // Init the screen
    curs_set(0); // Hide the cursor
    noecho(); // Don't show the input
    timeout(0); // Don't wait for the user to press a key (getch() function)
    resize_term(MAP_SIZE + 6, MAP_SIZE + 4); // Resize the terminal

    // Init the map
    int map[MAP_SIZE][MAP_SIZE];
    initMap(map);
    
    // Read the level
    file = fopen("cells.lvl", "r"); // Open the file
    if(file == NULL){
        printf("\nERROR: main() function => file variable is null\n");
        exit(1);
    }
    readLevel(map); // Read the file
    
    while(1){
        currentGeneration++;
        drawMap(map);
        updateMap(map);

        char ch = getch();
        if(ch == 'p'){
            while(1){
                curs_set(1);
                ch = getch();
                if(ch == 'p'){
                    break;
                }
            }
        }
        if(ch == 'q'){
            break;
        }
    }

    endwin();

    return 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~ Functions Definitions ~~~~~~~~~~~~~~~~~~~~~~~ //

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
    clear();
    drawBorder();
    mvprintw(1, 1, "Generation: %d", currentGeneration);
    for(int i = 0; i < MAP_SIZE; ++i){
        for(int j = 0; j < MAP_SIZE; ++j){
            if(map[i][j] == DEAD)
                mvprintw(i + 3, j + 1, "%c ", 32u); // 32u is the code for the character " "
            else
                mvprintw(i + 3, j + 1, "%c ", 248u); // 254u is the code for the character "°"
        }
    }
    // Pause button
    mvprintw(MAP_SIZE + 4, 1, "Press 'p' to pause");
    mvprintw(MAP_SIZE + 5, 1, "Press 'q' to quit");
    refresh();
    usleep(SLEEP_TIME * 1000);
}

void drawBorder(){
    // Corners
    mvprintw(2, 0, "%c", 201u);
    mvprintw(2, MAP_SIZE + 2, "%c", 187u);
    mvprintw(MAP_SIZE + 3, 0, "%c", 200u);
    mvprintw(MAP_SIZE + 3, MAP_SIZE + 2, "%c", 188u);

    // Top and bottom
    for(int i = 1; i <= MAP_SIZE + 1; ++i){
        mvprintw(2, i, "%c", 205u);
        mvprintw(MAP_SIZE + 3, i, "%c", 205u);
    }

    // Left and right
    for(int i = 3; i < MAP_SIZE + 3; ++i){
        mvprintw(i, 0, "%c", 186u);
        mvprintw(i, MAP_SIZE + 2, "%c", 186u);
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