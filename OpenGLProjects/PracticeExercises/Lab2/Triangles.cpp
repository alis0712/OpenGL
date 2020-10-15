/*
Syed Ali
COSC 518 Lab 2 Problem 1
Assignment Due 09/21/2020
*/

#include <glut.h>

void myinit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);						// set display window to white
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(-200.0, 400.0, -200.0, 200);					// setting the (x,y) coordinates
	glMatrixMode(GL_MODELVIEW);
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);

	// First House
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);

	glVertex2f(0, 70);									// making the roof of the first house
	glVertex2f(100, 150);
	glVertex2f(200, 70);
	glEnd();

	// Second House
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);

	glVertex2f(50, 60);									// making the roof of the second house
	glVertex2f(100, 100);
	glVertex2f(150, 60);
	glEnd();

	glFlush();

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA
		| GLUT_SINGLE | GLUT_MULTISAMPLE);			// initialize GLUT
	glutInitWindowSize(640, 480);					// set the window size
	glutInitWindowPosition(100, 100);				// set display-window width and height to 100
	glutCreateWindow("Drawing a 2D House");
	glutDisplayFunc(display);						// send graphics to display window
	myinit();
	glutMainLoop();
	return 0;
}