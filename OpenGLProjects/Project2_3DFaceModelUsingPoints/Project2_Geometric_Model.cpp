/*
Syed Ali 
COSC 518 Project 2 Geometric Modelling
Assignment Due: 10/19/2020
*/


#include <glut.h> 
#include <iostream>
#include <fstream>                                                                                                                                      // To read in a text file
#include <sstream>                                                                                                                                      // To read in a text file

using namespace std;


struct POINTS                                                                                                                                           // Defining a structure called points
{
    int      n;                                                                                                                                         // number of nodes
    float    x;                                                                                                                                         // x coordinate
    float    y;                                                                                                                                         // y coordinate
    float    z;                                                                                                                                         // z coordinate
    
};

POINTS point[1371];                                                                                                                                      // number of points in the text file is 1371

float sumx = 0;                                                                                                                                          // setting the sum x, sum y and sum z to zero
float sumy = 0;
float sumz = 0;
void initGL()                                                                                                                                            // initializing GL
{

    glClearColor(0.0, 0.0, 0.0, 0.0);                                                                                                                    // setting the window clear
    glMatrixMode(GL_PROJECTION);                                                                                                                         
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-200, 200.0, -200.0, 200, -300.0, 300);                                                                                                      // setting x, y, and z coordinates
}


void display()
{
    ifstream f;                                                                                                                                          // reading in a text file                                                                                                                                          
    f.open("points.txt");                                                                                                                                // reading in a series of points
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);                                                                                                                            // setting the point color to clear
    glPointSize(2);                                                                                                                                      // setting the point size to two
    glBegin(GL_POINTS);                                                                                                                                  // Beginning the GLPoints
   
    for (int i = 0; i < 1371; ++i)                                                                                                                       // for the size of points
    {
       
        f >> point[i].n >> point[i].x >> point[i].y >> point[i].z;                                                                                       // read in nodes, x, y and z coordinates
        cout << point[i].n << " " << point[i].x << " " << point[i].y << " " << point[i].z << endl;                                                       // print out the coordinates
        
        glVertex3f(point[i].x, point[i].y, point[i].z);                                                                                                  // plotting the series of points

    }

    
    glEnd();
    glFlush();
    f.close();
   
    glutSwapBuffers();
   
}


void reshape(int w, int h)                                                                                                                              // allows the window to be configured properly
{
    ifstream f;
    f.open("points.txt");
    for (int i = 0; i < 1371; ++i)
    {
        f >> point[i].n >> point[i].x >> point[i].y >> point[i].z;

        sumx += (point[i].x)/ 1371;                                                                                                                     // sum overall x, y and z coordinates
        sumy += (point[i].y)/ 1371;
        sumz += (point[i].z)/ 1371;
    }
    f.close();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (GLfloat)w / (GLfloat)h, 5.0, 300.0);                                                                                          // setting the viewing angle to 90, aspect ration of 1.33, zNear of 4.0 and zFar of 300.0
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(sumx, sumy, 0.0, sumx, sumy, sumz, 0, 1, 0);
}

int main(int argc, char* argv[]) 
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA| GLUT_SINGLE | GLUT_MULTISAMPLE);			                                                                             // initialize GLUT
    glutInitWindowSize(800, 600);					                                                                                                     // set the window size
    glutInitWindowPosition(100, 100);				                                                                                                     // set display-window width and height to 100
    glutCreateWindow("Plotting a 3D face using 3D Points");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);						                                                                                                     // send graphics to display window
    initGL();
    glutMainLoop();
    return 0;

}
