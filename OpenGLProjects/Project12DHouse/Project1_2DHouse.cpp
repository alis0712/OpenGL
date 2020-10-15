/*
Syed Ali
COSC 518 Project I 2D House
Assignement Due: 09/28/2020
*/

#include <glut.h>
#include<math.h>

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);			// Set display window color (R, G, B, Alpha)
	glMatrixMode(GL_PROJECTION);				// Set 2D transformation as gluOrtho2D(Min, Width, Max, Width, Min, Height, Max Height)
	gluOrtho2D(0.0, 800, 0.0, 600);				// setting axes for coordinates
}

void wheel(int x, int y)						// Function for drawing the wheels of the car
{
	float th;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		th = i * 3.142 / 180;
		glVertex2f(x + 10*cos(th), y + 10*sin(th));
	}
	glEnd();
}

void draw_pixel(GLint cx, GLint cy)				// function for plotting pixels for the moon
{
	glBegin(GL_POINTS);
	glVertex2f(cx, cy);
	glEnd();
}

void plotpixels(GLint h, GLint k,				// plotting pixels
	GLint x, GLint y)
{
	draw_pixel(x + h, y + k);
	draw_pixel(-x + h, y + k);
	draw_pixel(x + h, -y + k);
	draw_pixel(-x + h, -y + k);
	draw_pixel(y + h, x + k);
	draw_pixel(-y + h, x + k);
	draw_pixel(y + h, -x + k);
	draw_pixel(-y + h, -x + k);

}

void draw_circle(GLint h, GLint k,				// function for drawing the circle 
	GLint r)
{
	GLint d = 1 - r, x = 0, y = r;
	while (y > x)
	{
		plotpixels(h, k, x, y);
		if (d < 0) d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			--y;
		}
		++x;
	}
	plotpixels(h, k, x, y);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);				// clear display window


	int n;
	for (n = 0; n <= 200; n++)
	{
		glColor3f(1.0, 1.0, 1.0);
		draw_circle(800, 600, n);				// drawing the moon
	}
	
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5);
	glBegin(GL_POINTS);							// drawing the stars
	glVertex2f(25.0, 580.0);
	glVertex2f(50.0, 560.0);
	glVertex2f(75.0, 540.0);
	glVertex2f(100.0, 520.0);
	glVertex2f(150.0, 500.0);
	glVertex2f(200.0, 520.0);
	glVertex2f(250.0, 540.0);
	glVertex2f(300.0, 560.0);
	glVertex2f(350.0, 580.0);
	glVertex2f(400.0, 560.0);
	glVertex2f(450.0, 540.0);
	glVertex2f(500.0, 520.0);
	glVertex2f(550.0, 500.0);
	glVertex2f(600.0, 520.0);
	glVertex2f(620.0, 540.0);

	glEnd();



	glColor3f(0.8, 0.498039, 0.196078);			// Building the roof of the house
	glBegin(GL_POLYGON);
	glVertex2f(200.0, 500.0);
	glVertex2f(600.0, 500.0);
	glVertex2f(700.0, 350.0);
	glVertex2f(300.0, 350.0);
	glEnd();


	glColor3f(0.137255, 0.137255, 0.556863);	// Top Front Wall
	glBegin(GL_TRIANGLES);
	glVertex2f(200.0, 500.0);
	glVertex2f(100.0, 350.0);
	glVertex2f(300.0, 350.0);
	glEnd();

	glColor3f(0.5, 0.5, 0.0);					// Front Wall
	glBegin(GL_POLYGON);
	glVertex2f(100.0, 350.0);
	glVertex2f(300.0, 350.0);
	glVertex2f(300.0, 100.0);
	glVertex2f(100.0, 100.0);

	glEnd();

	glColor3f(0.85, 0.53, 0.10);				// Front Door
	glBegin(GL_POLYGON);
	glVertex2f(150.0, 250.0);
	glVertex2f(250.0, 250.0);
	glVertex2f(250.0, 100.0);
	glVertex2f(150.0, 100.0);
	glEnd();
	
	glColor3f(0.196078, 0.6, 0.8);		        // Front Door Lock
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2f(170, 170);
	glEnd();

	glColor3f(0.4, 0.4, 0.4);					// Side Wall
	glBegin(GL_POLYGON);
	glVertex2f(300.0, 350.0);
	glVertex2f(700.0, 350.0);
	glVertex2f(700.0, 100.0);
	glVertex2f(300.0, 100.0);
	glEnd();


	glColor3f(0.560784, 0.560784, 0.737255);	// Window One
	glBegin(GL_POLYGON);
	glVertex2f(330.0, 320.0);
	glVertex2f(450.0, 320.0);
	glVertex2f(450.0, 230.0);
	glVertex2f(330.0, 230.0);
	glEnd();

	glColor3f(0.0, 1.0, 1.0);					// Line of Window One
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(390.0, 320.0);
	glVertex2f(390.0, 230.0);
	glVertex2f(330.0, 273.0);
	glVertex2f(450.0, 273.0);
	glEnd();

	glColor3f(0.560784, 0.560784, 0.737255);	// Window Two
	glBegin(GL_POLYGON);
	glVertex2f(530.0, 320.0);
	glVertex2f(650.0, 320.0);
	glVertex2f(650.0, 230.0);
	glVertex2f(530.0, 230.0);
	glEnd();


	glColor3f(0.0, 1.0, 1.0);					// Lines of Window Two
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(590.0, 320.0);
	glVertex2f(590.0, 230.0);
	glVertex2f(530.0, 273.0);
	glVertex2f(650.0, 273.0);
	glEnd();

	glColor3f(0.847059, 0.847059, 0.74902);	     // Entrance Path
	glLineWidth(3);
	glBegin(GL_POLYGON);
	glVertex2f(150.0, 100.0);
	glVertex2f(250.0, 100.0);
	glVertex2f(210.0, 0.0);
	glVertex2f(40.0, 0.0);
	glEnd();

	glColor3f(1.000, 0.000, 0.000);				 // Bottom of the car
	glBegin(GL_POLYGON);
	glVertex2f(100, 50);
	glVertex2f(100, 80);
	glVertex2f(290, 80);
	glVertex2f(290 , 50);
	glEnd();

	
	glColor3f(1.000, 0.000, 0.000);				// Front of the car
	glBegin(GL_POLYGON);
	glVertex2f(120, 80);
	glVertex2f(150, 110);
	glVertex2f(240, 110);
	glVertex2f(270, 80);
	glEnd();
	
	wheel(120, 50);								// the two wheels of the car
	wheel(260, 50);
	
	glFlush();									// Process all OpenGL routine as quickly as possible

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);						 // Initialize GLUT
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode

	glutInitWindowPosition(100, 100);			 // Set top - left display window position.

	glutInitWindowSize(800, 600);				 // Set display window width and height

	glutCreateWindow("2D House in OpenGL ");	 // Create display window with the given title

	init();										 // Execute initialization procedure

	glutDisplayFunc(display);					 // Send graphics to display window

	glutMainLoop();								 // Display everything and wait.

}





