#include <GL/glut.h>
#include <GL/gl.h>
#include "game.h"

int gridX, gridY;
short sDirection = RIGHT;

extern bool gameOver;
// make variables to track position of snake
// make init pos at cenetre of screen
int posX = 20, posY = 20;

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
	
	// if x coord is 0 or y coord is 0 or x coord is at end of screen
	// or y coord is at end of screen
	if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1)
	{
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 0.0);
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

void drawSnake()
{
	// results of condition casing set in main.cpp (but gotta fully
	// understand how that works first) b4 i move onto this part
	if (sDirection == UP)
		posY++;
	else if (sDirection == DOWN)
		posY--;
	else if (sDirection == RIGHT)
		posX++;
	else if (sDirection == LEFT)
		posX--;
	
	glRectd(posX, posY, posX + 1, posY + 1);

	//now check if snake is "drawn" in the red area:
	// remember gridX - 1 = 39
	if (posX == 0 || posX == gridX - 1 || posY == 0 || posY == gridY - 1)
	{
		gameOver=true;
	}
}