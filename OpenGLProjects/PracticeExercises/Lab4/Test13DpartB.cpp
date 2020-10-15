/*3D Geometry Test*/


/*
 *
 *
 tasks:
 1) Run the program
 2)try changing viewer location so you can see the objects from the bottom of the scene.
 3) change the size of these 3D objects ( cube and torus, cone – twice bigger, sphere – ¼ smaller ).


 *
 *
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>


 // Base of the display lists.
GLuint lists;


// The right cube can be rotated.  Whoopee.
static GLfloat theta[] = { 45.0,0.0,0.0 };
static GLint axis = 2;

/* initial viewer location */
static GLdouble viewer[] = { 0.0, -20.0, 0.005 };




// Paint the scene.
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Update viewer position in modelview matrix */
	glLoadIdentity();

	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);


	glPushMatrix();

	// Left cube.
	glTranslatef(-2.0, 0.0, 0.0);
	glCallList(lists + 1);

	// Sphere centered at origin.
	glTranslatef(2.0, 0.0, 0.0);
	glCallList(lists + 2);

	// Right cube.
	glTranslatef(2.0, 0.0, 0.0);
	// Rotate cube.
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glCallList(lists + 1);

	// Now that I'm thoroughly confused, let's re-establish the
	// origin.
	glPopMatrix();

	// The cone.
	// Up y-axis by 1.
	glTranslatef(0.0, 1.0, 0.0);
	// Rotate z-axis up to y-axis.
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glCallList(lists + 3);

	// The torus.
	// Translate up the cone.
	glTranslatef(0.0, 0.0, 1.0);
	glCallList(lists + 4);

	glutSwapBuffers();
}


// Rotate the right cube.  Looks kinda neat when it cuts into
// the sphere.
void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
	theta[axis] += 2.0;
	if (theta[axis] > 360.0) theta[axis] -= 360.0;
	glutPostRedisplay();
}


void keys(unsigned char key, int x, int y)
{

	/* Use x, X, y, Y, z, and Z keys to move viewer */

	if (key == 'x') viewer[0] -= 1.0;
	if (key == 'X') viewer[0] += 1.0;
	if (key == 'y') viewer[1] -= 1.0;
	if (key == 'Y') viewer[1] += 1.0;
	if (key == 'z') viewer[2] -= 1.0;
	if (key == 'Z') viewer[2] += 1.0;
	if (key == 'l') glDisable(GL_LIGHT1);
	if (key == 'L') glEnable(GL_LIGHT1);
	if (key == ' ') exit(0);

	printf("v[x]: %f, v[y]: %f, v[z]: %f.\n",
		viewer[0], viewer[1], viewer[2]);

	glutPostRedisplay();
}


void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);

	/* Use a perspective view */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35.0, (GLfloat)w / h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}




// Set material and light values.
void init(void)
{

	glClearColor(0.2f, 0.3f, 0.4f, 1.0);
}


int
main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D geometry hands on");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	init();

	// Get five list handles.
	lists = glGenLists(5);

	// For the moving light.
	glNewList(lists, GL_COMPILE);
	glutSolidCube(0.1);
	glEndList();

	// For the two cubes.
	glNewList(lists + 1, GL_COMPILE);
	glutSolidCube(2.0);
	glEndList();

	// The sphere at the origin.
	glNewList(lists + 2, GL_COMPILE);
	glutSolidSphere(1.0, 32, 32);
	glEndList();

	// The cone.
	glNewList(lists + 3, GL_COMPILE);
	glutSolidCone(1.0, 2.0, 32, 32);
	glEndList();

	// The torus.
	glNewList(lists + 4, GL_COMPILE);
	glutSolidTorus(0.25, 1.0, 32, 32);
	glEndList();

	glutMainLoop();
	return 0;
}

