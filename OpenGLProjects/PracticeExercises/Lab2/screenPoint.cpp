/*
Syed Ali
COSC 518 Lab 2 Problem 2a
Assignment Due 09/21/2020
*/

#include <glut.h>

class screenPoint
{
private:
	GLint x, y;

public:
	screenPoint()											 // Default Constructor : Initializes coordinates position(0, 0)
	{
		x = 0;
		y = 0;
	}


	void setCoordinates(GLint xCoordinateValue, GLint yCoordinateValue)
	{
		x = xCoordinateValue;
		y = yCoordinateValue;
	}

	GLint getx() const
	{
		return x;
	}

	GLint gety() const
	{
		return y;
	}

	void incrementx()
	{
		x++;
	}

	void decrementy()
	{
		y--;
	}
};

void setPixel(GLint xCoordinate, GLint yCoordinate)
{
		glBegin(GL_POINTS);
		glVertex2i(xCoordinate, yCoordinate);

		glEnd();
		glFlush();                                         // process all OpenGL functions as quickly as possible
}

void circleMidPoint(GLint xc, GLint yc, GLint radius)
{
	screenPoint circlePoint;      						   // Initialize value for midpoint parameter
	GLint p = 1 - radius;								   // set coordinates for top point of circle
	circlePoint.setCoordinates(0, radius);


	void circlePlotPoints(GLint, GLint, screenPoint);	   // function prototype

	circlePlotPoints(xc, yc, circlePoint);				   // plot initial point in each quadrant

	while (circlePoint.getx() < circlePoint.gety())		   // calculate the next point and plot in each octant
	{
		circlePoint.incrementx();
		if (p < 0)
		{
			p += 2 * circlePoint.getx() + 1;
		}

		else
		{
			circlePoint.decrementy();
			p += 2 * (circlePoint.getx() - circlePoint.gety()) + 1;
		}

		circlePlotPoints(xc, yc, circlePoint);
	}
}

void circlePlotPoints(GLint xc, GLint yc,				  // setting the points for the circle
	screenPoint circPoint)
{
	setPixel(xc + circPoint.getx(), yc + circPoint.gety());
	setPixel(xc - circPoint.getx(), yc + circPoint.gety());
	setPixel(xc + circPoint.getx(), yc - circPoint.gety());
	setPixel(xc - circPoint.getx(), yc - circPoint.gety());

	setPixel(xc + circPoint.gety(), yc + circPoint.getx());
	setPixel(xc - circPoint.gety(), yc + circPoint.getx());
	setPixel(xc + circPoint.gety(), yc - circPoint.getx());
	setPixel(xc - circPoint.gety(), yc - circPoint.getx());
}


void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);						// set display window to white
	glMatrixMode(GL_PROJECTION);							// set projection parameters
	gluOrtho2D(0.0, 300.0, 0.0, 300);


}

void drawMyCircle()
{
	glClear(GL_COLOR_BUFFER_BIT);							// clear display window
	glColor3f(1.0, 0.0, 0.0);								// set the pixel color to red
	glPointSize(3.0);

	GLint xCenter = 150;
	GLint yCenter = 150;
	GLint radius = 50;
	circleMidPoint(xCenter, yCenter, radius);

	glFlush();

}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);								    // initialize GLUT
	glutInitWindowSize(500, 500);							// set the window size
	glutInitWindowPosition(10, 10);						    // set display-window width and height to 500
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);			// set display mode

	glutCreateWindow("Circle using Mid Point Algorithm ");  // Now display the window with a title
	myinit();
	glutDisplayFunc(drawMyCircle);							// send graphics to display window
	glutMainLoop();
}
