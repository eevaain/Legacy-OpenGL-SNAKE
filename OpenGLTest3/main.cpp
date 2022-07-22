// REMEMBER FILE HAS TO BE CALLED MAIN TO LINK OTHER SHITS
#include "game.h"
#include <GL/freeglut.h> // HOLY SHIT I FIXED IT OK SO I NEEDED THIS
#include <GL/glut.h>


//make some constants 
#define COLUMNS 40
#define ROWS 40

// we write this function definition so that we can write its body
// at the bottom??? it works when i have the function body at the top. 
// remember it only runs inside of main()
void display_callback();
void reshape_callback(int, int);

void init()
{
	glClearColor(0.0, .0,1.0, 1.0);

	// we initialize our grid right here
	initGrid(COLUMNS, ROWS);

}

int main(int argc, char** argv) // ???
{

	glutInit(&argc, argv); //pointer and pointer to a pointer
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // init display mode
	glutInitWindowSize(500, 500); //init window size
	glutCreateWindow("SNAKE"); // creates window
	glutDisplayFunc(display_callback); //passing func in func
	glutReshapeFunc(reshape_callback);
	// callbacks are passing functions as arguments to another func?
	init(); // this thing allows us to plot our shit on the window?
	glutMainLoop();// keeps our program running in a loop 
	// im assuming this func is connected to all the stuff in prev lines?

	return 0;
}
// this is our callback function 
void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	glutSwapBuffers();//puts the thing on the screen using double buffering
	// so when one frame is processing onto the screen, another frame is 
	// already put on. goal: always have a frame present at the front. 
	// we dont want a loading frame at the front
	// so imagine a shakespearean play 
	// WE WANT THERE TO BE NO GAP BETWEEN SCENES
}

void reshape_callback(int w, int h)
{
	//we need to set the viewport
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// make 40x40 coordinate system for window
	//-1 popping out on screen
	// 1 behind screen -> we plot our pixels on 0 for z so it is visible
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}
