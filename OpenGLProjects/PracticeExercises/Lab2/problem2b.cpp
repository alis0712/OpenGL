/*
Syed Ali
COSC 518 Lab 2 Problem 2b
Assignment Due 09/21/2020
Reference: https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl#:~:text=6%20Answers&text=It%20looks%20like%20immediately%20after,immediately%20and%20drawing%20the%20square.
*/

#include <glut.h>
#include <math.h>


void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);			// get the current angle

		float x = r * cosf(theta);                                                  // calculate the x component
		float y = r * sinf(theta);                                                  // calculate the y component

		glVertex2f(x + cx, y + cy);                                                 // output vertex

	}
	glEnd();
	glFlush();


}

void Draw()																			// a function that draws the circle on the screen
{
	DrawCircle(0.5, 0.5, 0.2, 100);													// specifying the center x radius, the center y radius and the number of segments
	glEnd();
	glFlush();
}

void init()																			// initializing 
{
	glClearColor(1.0, 1.0, 1.0, 1.0);												// setting the background window white
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int iArgc, char** cppArgv) 
{
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);									// initialize GLUT
	glutInitWindowSize(500, 500);													// set the window size
	glutInitWindowPosition(10, 10);													// set display-window width and height to 500
	glutCreateWindow("2D Circle");													// set display mode
	init();
	glutDisplayFunc(Draw);															// send graphics to display window
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glutMainLoop();
	return 0;

}