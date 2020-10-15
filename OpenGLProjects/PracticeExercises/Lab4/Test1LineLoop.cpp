/*
Syed Ali
COSC 518 Test1
Assignment Due 10/12/2020
*/

#include <glut.h>

void myinit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);						// set display window to white
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, 20, 0, 20);					// setting the (x,y) coordinates
	glMatrixMode(GL_MODELVIEW);
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);

	glColor3f(1.0, 0.0, 0.0);								// setting the object color to red
	glBegin(GL_LINE_LOOP);										// calling GL_POINTS functions

	glVertex2f(0, 5.5);										// placing all the points for the first house
	glVertex2f(5, 5);
	glVertex2f(6.5, 0);
	glVertex2f(9, 5);
	glVertex2f(14, 5.5);
	glVertex2f(10.5, 9);
	glVertex2f(12, 14);
	glVertex2f(6.5, 11.5);
	glVertex2f(12, 14);
	glVertex2f(6.5, 11.5);
	glVertex2f(2, 14);
	glVertex2f(3.5, 9);
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
	glutCreateWindow("Drawing a 2D Star");
	glutDisplayFunc(display);						// send graphics to display window
	myinit();
	glutMainLoop();
	return 0;
}