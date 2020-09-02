#include <glut.h> 
//#include<math.h>

void myinit(void)
{

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	//glMatrixMode(GL_MODELVIEW);
}



void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	glBegin(GL_TRIANGLES);


	glVertex2f(300.0, 110.0);
	glVertex2f(240.0, 115.0);
	glVertex2f(320.0, 250.0);

	glEnd();

	glFlush();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("draw trangle");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
	return 0;
}
