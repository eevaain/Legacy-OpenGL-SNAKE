#include <GL/glut.h>
#include <GL/gl.h>
#include "game.h"
#include <ctime>
#include <iostream>


int gridX, gridY;
int snake_length = 4; // init length of snake
short sDirection = RIGHT;


bool food = true;
int foodX, foodY;

extern bool gameOver;
extern int score;

// make init pos at cenetre of screen
// we make arrays of length 60 
// all these values below represent positions of init snake body pixels
int posX[60] = { 12,12,12,12 }, posY[60] = { 12,11,10,9 };


void initGrid(int x, int y)
{
	gridX = x;
	gridY = y;
}

void unit(int, int); //wait why are we putting definition here?
void drawGrid()
{
	// make a for loop to make the grid out of the small units
	for (int x = 0; x < gridX; x++)
	{
		for (int y = 0; y < gridY; y++)
		{
			unit(x, y);
		}
	}
}

// defining dimensions of a single unit
void unit(int x, int y)
{   // between glBegin and glEnd we draw all our stuff here
	
	//defining the border
	// if x coord is 0 or y coord is 0 or x coord is at end of screen
	// or y coord is at end of screen
	if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1)
	{
		glColor3f(0.0, 1.0, 0.0);
		glRectf(x, y, x + 1, y + 1);
	}
	else
	{
		//we add back the old code since we turned this entire block into an
		// if else condition so we can create different color block to represent
		// border blocks
		glLineWidth(1.0);
		glColor3f(1.0, 1.0, 1.0);
	}

	glBegin(GL_LINE_LOOP); // this argument sees all the code from
	// glBegin to glEnd and connects the coordinate points into a square
		glVertex2f(x, y);
		glVertex2f(x + 1, y);
		glVertex2f(x + 1, y + 1);
		glVertex2f(x, y + 1);
	glEnd();
}

void drawFood()
{
	// food will be drawn in random position from 1-38 since 0 & 39 are boundaries
	// we need to get two random numbers -> random coord x and random y
	// remember food can only be drawn ONCE SNAKE EATS IT

	if (food)
		//'random' void function is invoked here
		random(foodX, foodY); // if food true then pos of food change
	food = false; // immediately set to false after
	// this draws the single unit of food?
	glColor3f(1.0, 0.0, 0.0); // color of food
	glRectf(foodX, foodY, foodX + 1, foodY + 1);
}

void drawSnake()
{
	// something to do with 3rd element becoming 2nd element and then ascending
	// or descending moving positions... gotta replay that part
	for (int i = snake_length - 1; i > 0; i--)
	{
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];
		// when the snake moves, the body behind it must decrement
		// while it increments in the direction it moves in. 

	
	}
	// results of condition casing set in main.cpp (but gotta fully
	// understand how that works first) b4 i move onto this part
	if (sDirection == UP)
		posY[0]++;
	else if (sDirection == DOWN)
		posY[0]--;
	else if (sDirection == RIGHT)
		posX[0]++;
	else if (sDirection == LEFT)
		posX[0]--;

	for (int i = 0; i < snake_length; i++)
	{

		// remember cus i starts at index 0 
		if (posX[0] == posX[i + 1] && posY[0] == posY[i + 1])
			gameOver = true;

		if (i == 0)
			glColor3f(0.0, 1.0, 0.0);
		else
			glColor3f(0.0, 1.0, 0.0);
		glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);


	
	}

	//now check if snake is "drawn" in the red area:
	// remember gridX - 1 = 39

	// ep 7: WE NEED COLLISION DETECTION FOR HEAD WITH BORDER
	// index 0 is the head element
	if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1)
		gameOver=true;
	
	// make collision detection if snake hits food it means it ate food
	// meaning score + 1 and pos of food must be reset
	// so if head of snake and food are OVERLAPPING then run 
	// we want to check collision of HEAD and FOOD
	if (posX[0] == foodX && posY[0] == foodY)
	{
		score++;
		snake_length++;
		if (snake_length > MAX)
			snake_length = MAX;
		food = true;

	}

	//if (posX[0] == 6)
		//gameOver = true;
	// ^^ so this means if head pos is at x= 6, then stop game. 

}

// '&' takes "arguments by reference"
void random(int &x, int &y) // what do the &s do??
{
	int _maxX = gridX - 2; //38 units horizontally
	int _maxY = gridY - 2; //38 units vertically
	int _min = 1; // value of 1 because minimum range spawn of food must be
	// within 1-38, inclusive
	//we want to make sure random number is diff everyimt
	// for that we use computer time
	srand(time(NULL));
	x = _min + rand() % (_maxX - _min);
	//std::cout << x << std::endl;
	y = _min + rand() % (_maxY - _min);
	//std::cout << y << std::endl;
}
/// OHHH BEFORE I MISTYPED AND PUT '&' INSTEAD OF '%'


/// make init pos at cenetre of screen
//int posX = 20, posY = 20;
// ^^ this was once initial position of single cube when we were
// first testing but now we can make an entire snake body so we use arrays

// update: from cube -> snake : had to change how we draw the snake 
// and need to change collision detection