#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

void initGrid(int, int);
void drawGrid();
void drawSnake(); 
void drawFood();
void random(int&, int&); //wtf does int& mean

#endif