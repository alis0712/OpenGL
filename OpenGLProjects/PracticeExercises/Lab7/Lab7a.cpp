/*

Example animation using GLUT routines.
Draw a shiny sphere with a rotating cube in front of it.
Jie Yan Nov. 3. 2015

Modified By Syed F. Ali Due Nov 23rd, 2020
Try:
Task1: Change the sphere to another cube
Task2: Make the cube rotate in another direction


*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

/* light position */
GLfloat  lightPos[] = { 1.0, 1.0, 1.0, 0.0 };

/* light contribution */
GLfloat  ambientLight[] = { 0.3, 0.3, 0.3, 0.0 };
GLfloat  diffuseLight[] = { 0.7, 0.7, 0.7, 0.0 };
GLfloat  specularLight[] = { 1.0, 1.0, 1.0, 0.0 };

/* two examples of specular contributions */
GLfloat  shiny_surface[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat  diffuse_surface[] = { 0.0, 0.0, 0.0, 0.0 };


/******************************************************************************
Draw a shiny sphere with a rotating cube in front of it.
******************************************************************************/

void draw_scene(int i)
{
    glPushMatrix();

    /* specify the camera position (from, at, up) */

    gluLookAt(0.0, 0.0, 80.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    /* green stationary sphere */

    /* shiny surface */
    glMaterialfv(GL_FRONT, GL_SPECULAR, shiny_surface);
    glMateriali(GL_FRONT, GL_SHININESS, 128);

    glColor3f(0.0, 1.0, 0.0);

    glPushMatrix();
    glTranslatef(0.0, 0.0, -100.0);
    glRotatef(20.0, 0.0, 1.0, 0.0);
    glRotatef(35.0, 1.0, 0.0, 0.0);
    glutSolidCube(80);
    glPopMatrix();

    /* white rotating cube */

    /* no specular contribution */
    glMaterialfv(GL_FRONT, GL_SPECULAR, diffuse_surface);

    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glRotatef((float)i, 0.0, 1.0, 0.0);
    glutSolidCube(25.0);
    glPopMatrix();

    glPopMatrix();
}


/******************************************************************************
The actual animation loop that creates multiple frames.
******************************************************************************/

void display()
{
    int i;

    /* render a number of frames of animation */

    for (i = 0; i < 600; i++) {

        /* clear the color and z-buffer */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* set up the perspective transformation */
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, 1.0, 1.0, 1000.0);

        /* from now on we're affecting the modeling matrix */
        glMatrixMode(GL_MODELVIEW);

        /* draw our scene */
        draw_scene(i);

        /* swap that performs double-buffering */
        glutSwapBuffers();
    }
}


/******************************************************************************
Initilize various graphics things such as surface material and lights.
******************************************************************************/

void init_graphics()
{
    /* enable depth buffering */
    glEnable(GL_DEPTH_TEST);

    /* surface shading info */
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);

    /* these lines allow the diffuse and ambient color to be set by */
    /* the gtColor3f() commands that proceed an object */

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    /* turn on lighting */
    glEnable(GL_LIGHTING);

    /* create intensity contributions of the light */
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

    /* specify the light position */
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    /* turn on light zero */
    glEnable(GL_LIGHT0);

    /* select clearing color */
    glClearColor(0.0, 0.0, 0.0, 0.0);
}


/******************************************************************************
Process a keyboard action.  In particular, exit the program when an
"escape" is pressed in the window.
******************************************************************************/

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}


/******************************************************************************
Main routine.
******************************************************************************/

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init_graphics();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

