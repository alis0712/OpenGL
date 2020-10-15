/*
Syed Ali
COSC 518 Test1
Assignment Due 10/12/2020
*/

#include <glut.h>
#include <math.h>

void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glColor3f(0.0, 1.0, 0.0);
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

void myinit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);						// set display window to white
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(-20, 20, -20, 20);					// setting the (x,y) coordinates
	glMatrixMode(GL_MODELVIEW);
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);

	glColor3f(1.0, 0.0, 0.0);								// setting the object color to red
	glPointSize(2);
	glBegin(GL_LINE_LOOP);										// calling GL_POINTS functions

	glVertex2f(5, 5);										// placing all the points for the first house
	glVertex2f(6.5, 0);
	glVertex2f(9, 5);
	glVertex2f(14, 5.5);
	glVertex2f(10.5, 9);
	glVertex2f(12, 14);
	glVertex2f(6.5, 11.5);
	glVertex2f(2, 14);
	glVertex2f(3.5, 9);
	glVertex2f(0, 5.5);
	glVertex2f(5, 5);
	glEnd();


	glColor3f(1.0, 0.0, 0.0);								// setting the object color to red
	
	glBegin(GL_TRIANGLE_FAN);										// calling GL_POINTS functions

	glVertex2f(7, 7);										// placing all the points for the first house
	glVertex2f(5, 5);
	glVertex2f(9, 5);
	glVertex2f(7, 7);
	glVertex2f(9, 5);
	glVertex2f(10.5, 9);
	glVertex2f(7, 7);
	glVertex2f(10.5, 9);
	glVertex2f(6.5, 11.5);
	glVertex2f(7, 7);
	glVertex2f(6.5, 11.5);
	glVertex2f(3.5,9);
	glVertex2f(7, 7);
	glVertex2f(3.5, 9);
	glVertex2f(5, 5);

	glEnd();

	glColor3f(1.0, 0.0, 0.0);								// setting the object color to red
	
	glBegin(GL_POLYGON);										// calling GL_POINTS functions

	glVertex2f(5, 5);										// placing all the points for the first house
	glVertex2f(9, 5);
	glVertex2f(10.5, 9);
	glVertex2f(6.5, 11.5);
	glVertex2f(3.5, 9);

	glEnd();

	glColor3f(1.0, 0.0, 0.0);								// setting the object color to red
	
	glBegin(GL_TRIANGLE_STRIP);	
	
	// dEe
	glVertex2f(3.5, 9);
	glVertex2f(0, 5.5);
	glVertex2f(5, 5);
	
	//Oea
	glVertex2f(7, 7);
	glVertex2f(3.5, 9);
	glVertex2f(5, 5);

	//Oab
	glVertex2f(7, 7);										// placing all the points for the first house
	glVertex2f(5, 5);
	glVertex2f(9, 5);

	//Obc
	glVertex2f(7, 7);
	glVertex2f(9, 5);
	glVertex2f(10.5, 9);

	//bCc
	glVertex2f(9, 5);
	glVertex2f(14, 5.5);
	glVertex2f(10.5, 9);
	glEnd();


	glColor3f(1.0, 0.0, 0.0);								// setting the object color to red
	glBegin(GL_QUADS);

	
	glVertex2f(5, 5);
	glVertex2f(6.5, 0);
	glVertex2f(9, 5);

	
	glVertex2f(10.5, 9);
	glVertex2f(14, 5.5);
	
	glVertex2f(6.5, 11.5);										// placing all the points for the first house
	glVertex2f(2, 14);
	glVertex2f(3.5, 9);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);								// setting the object color to red
	

	DrawCircle(7, 7, 7, 100);													// specifying the center x radius, the center y radius and the number of segments
	glEnd();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA
		| GLUT_SINGLE | GLUT_MULTISAMPLE);			// initialize GLUT
	glutInitWindowSize(800, 600);					// set the window size
	glutInitWindowPosition(100, 100);				// set display-window width and height to 100
	glutCreateWindow("Drawing a 2D Star");
	glutDisplayFunc(display);						// send graphics to display window
	myinit();
	glutMainLoop();
	return 0;
}