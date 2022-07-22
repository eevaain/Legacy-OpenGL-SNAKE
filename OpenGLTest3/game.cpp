#include <GL/glut.h>
#include <GL/gl.h>
#include "game.h"

int gridX, gridY;

void initGrid(int x, int y)
{
	gridX = x;
	gridY = y;
}

void unit(int, int); //wait why are we putting definition here?
void drawGrid()
{
	unit(20, 20);
}

// defining dimensions of a single unit
void unit(int x, int y)
{   // between glBegin and glEnd we draw all our stuff here

	glLineWidth(1.0);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINE_LOOP); // this argument sees all the code from
	// glBegin to glEnd and connects the coordinate points into a square
		glVertex2f(x, y);
		glVertex2f(x + 1, y);
		glVertex2f(x + 1, y + 1);
		glVertex2f(x, y + 1);
	glEnd();
}