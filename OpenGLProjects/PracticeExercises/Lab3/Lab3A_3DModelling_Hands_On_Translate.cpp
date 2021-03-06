/*
Syed Ali
COSC 518 Computer Graphics I
Lab 3A 3D Modelling Hands On
*/

#include <glut.h>

void init(void)

{

	glClearColor(0.0, 0.0, 0.0, 0.0);							  // set the color clear

	glShadeModel(GL_FLAT);

}

void display(void)

{

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);

	glLoadIdentity();											 // clear the matrix


	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);     // viewing transformation


	glScalef(1.0, 2.0, 1.0);									// modeling transformation

	glTranslatef(1.5, 1.0, 1.0);								// Translating the cube by a factor of 2
	
	glutWireCube(1.0);

	glFlush();

}

void reshape(int w, int h)

{

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	glMatrixMode(GL_MODELVIEW);

}

int main(int argc, char** argv)

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 500);

	glutInitWindowPosition(100, 100);

	glutCreateWindow(argv[0]);

	init();

	glutDisplayFunc(display);

	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;

}