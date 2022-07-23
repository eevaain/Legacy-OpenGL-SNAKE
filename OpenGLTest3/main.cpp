// REMEMBER FILE HAS TO BE CALLED MAIN TO LINK OTHER SHITS
// IN SOLUTION SETTINGS GO TO ADVANCED AN ENABLE MULTI-BYTE CHARACTER SET
#include "game.h"
#include <GL/freeglut.h> // HOLY SHIT I FIXED IT OK SO I NEEDED THIS!!!
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

//make some constants 
#define COLUMNS 25
#define ROWS 25

//define constant for FPS
#define FPS 7

// extern is used when refering to variables in another file
// we use short cus we dont need a 32 bit integer
extern short sDirection;
//^^ still gotta fully understand what extern does
bool gameOver = false;

int score = 0;


// we write this function definition so that we can write its body
// at the bottom??? it works when i have the function body at the top. 
// remember it only runs inside of main()

void keyboard_callback(int, int, int); // notice how we define all the types here
void timer_callback(int);
void display_callback();
void reshape_callback(int, int);

void init()
{
	glClearColor(0.0, 0.0,0.0, 1.0);

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


	glutTimerFunc(0, timer_callback, 0);

	// takes a keyboard callback
	// we use arrow keys -> glut already has defined constants for them
	// glutSpecialFunc sets argument as a callback for current window
	// ^^ KEY WORD HERE IS CURRENT WINDOW!!!!
	// ^^ ALSO ALLOWS to run callback when user presses "special keys" 
	// callback parameter is a GLUT_KET constant
	// wait do we assume that the parameters (int key, int, int) are 
	// already included here??? yooo??? 
	// wait so at the end of glutSpecialFunc, then keyboard_callback is invoked?
	glutSpecialFunc(keyboard_callback);
	// callbacks are a way to ensure certain code doesnt run until
	// other code is done running
	// ^^ wait but how is the input of the key put in here???
	// wait so imagine we run key_board callback as is... well we need
	// something running to listen to the keyboard callback... is that
	// why we have something like glutSpecialFunc to keep on running
	// in main because its not like we're always going to give the function
	// keyboard_callback input? so is this async programming? 
	// WAIT HOLD UP SO IS glutSpecialFunc like our event listener??? 

	// callbacks are passing functions as arguments to another func?
	init(); // this thing allows us to plot our shit on the window?
	glutMainLoop();// keeps our program running in a loop 
	// im assuming this func is connected to all the stuff in prev lines?

	return 0;
}
// this is our callback function 

int index = 0; // keep track of position of cube
void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	drawSnake();
	drawFood();
	glutSwapBuffers();//puts the thing on the screen using double buffering
	// so when one frame is processing onto the screen, another frame is 
	// already put on. goal: always have a frame present at the front. 
	// we dont want a loading frame at the front
	// so imagine a shakespearean play 
	// WE WANT THERE TO BE NO GAP BETWEEN SCENES
	// tiny delay is added by glutSwapBuffers so frame rate is not exactly 10
	
	//at end of display callback there will be a new frame -> this is baseline
	// for FPS

	if (gameOver)
	{
		// 10 char = 10 bytes
		char _score[10];
		_itoa_s(score, _score, 10);
		char text[50] = "Your score: ";
		strcat_s(text, _score);
		// had to add in L because my win32 API expects wide str
		MessageBox(NULL, text, "GAME OVER", 0);
		exit(0);
	}
	//std::cout << score << std::endl;
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

// new frame will be displayed every time this function is called
void timer_callback(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer_callback, 0);
}

// i dont really understnad this part... gotta get back to it
void keyboard_callback(int key, int, int)
{
	// switches vs if else -> if else tests expression based on range
	// switches test on discrete data values
	// switch takes input of key
	switch (key)
	{
	case GLUT_KEY_UP:
		if (sDirection != DOWN)
		{
			sDirection = UP;
			break;
		}
	case GLUT_KEY_DOWN:
		if (sDirection != UP)
		{
			sDirection = DOWN;
			break;
		}
	case GLUT_KEY_RIGHT:
		if (sDirection != LEFT)
		{
			sDirection = RIGHT;
			break;
		}
	case GLUT_KEY_LEFT:
		if (sDirection != RIGHT)
		{
			sDirection = LEFT;
			break;
		}
	}
}


// THIS USED TO BE IN DISPLAY CALLBACK
// draws a rectangle using the two points given (so its 2x2)
	// same thing as glVertex x4
	//x1 = x coord of rectangle vertex
	// x2 = opp vertex coord
	// ^^ with x,y twice, defining 2 points
//glRectd(index, 20, index + 2, 22); // y is gonna stay the same
// the function is only moving across x
//index++;
//if (index > 40)
//{
	//index = 0;
//}