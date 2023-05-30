#include <GL/glut.h>
#include <stdlib.h>


const int uOrder = 4;
const int vOrder = 4;


void initlights(void)
{
    GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat mat_diffuse[] = { 0.7, 0.8, 0.9, 1.0 };
    GLfloat mat_specular[] = { 0.9, 0.8, 0.7, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    GLfloat light[] = { 1, 1, 1 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
}


void init(void)
{
   
    glClearColor(0.0, 0.0, 0.0, 0.0);
   // glEnable(GL_DEPTH_TEST);
   /* glEnable(GL_MAP2_VERTEX_3);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, uOrder, 0, 1, 12, vOrder, &controlPointsGround[0][0][0]);*/
   // glEnable(GL_AUTO_NORMAL);
    glMapGrid2f(5.0, 0.0, 1.0, 5.0, 0.0, 1.0);
    initlights();   // for lighted version only

   
}

void drawcontrolPoints(GLfloat controlPoints[uOrder][vOrder][3])
{
    int i, j;
    float u, v;

    glEnable(GL_MAP2_VERTEX_3);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, uOrder, 0, 1, 12, vOrder, &controlPoints[0][0][0]);

    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2);

    const int n1 = 8, n2 = 30;
    for (i = 0; i <= n1; i++)
    {
        v = (float)i / n1;
        glBegin(GL_LINE_STRIP);
        for (j = 0; j <= n2; j++)
        {
            u = (float)j / n2;
            glEvalCoord2f(u, v);
        }
        glEnd();
    }

    for (i = 0; i <= n1; i++)
    {
        u = (float)i / n1;
        glBegin(GL_LINE_STRIP);
        for (j = 0; j <= n2; j++)
        {
            v = (float)j / n2;
            glEvalCoord2f(u, v);
        }
        glEnd();
    }

    for (i = 0; i <= n1; i++)
    {
        u = (float)i / n1;
        glBegin(GL_LINE_STRIP);
        for (j = 0; j <= n2; j++)
        {
            v = (float)j / n2;
            glEvalCoord2f(u, v);
        }
        glEnd();
    }

    for (i = 0; i <= n1; i++)
    {
        u = (float)i / n1;
        glBegin(GL_LINE_STRIP);
        for (j = 0; j <= n2; j++)
        {
            v = (float)j / n2;
            glEvalCoord2f(u, v);
        }
        glEnd();
    }

    for (i = 0; i <= n1; i++)
    {
        u = (float)i / n1;
        glBegin(GL_LINE_STRIP);
        for (j = 0; j <= n2; j++)
        {
            v = (float)j / n2;
            glEvalCoord2f(u, v);
        }
        glEnd();
    }
}

void display(void)
{
    int i, j;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    gluLookAt(10, 10, 10, 0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    GLfloat controlPointsRoof[uOrder][vOrder][3] =
    {
     {{-3.0, 2.0, -3.0}, {-0.5, 4.0,-3.0 }, {0.5, 4.0, -3.0 }, {3.0, 2.0,-3.0}},
     {{-3.0, 2.0, -1.0}, {-0.5, 4.0,-1.0 }, {0.5, 4.0, -1.0 }, {3.0, 2.0,-1.0}},
     {{-3.0, 2.0,  1.0}, {-0.5, 4.0, 1.0 }, {0.5, 4.0,  1.0 }, {3.0, 2.0, 1.0}},
     {{-3.0, 2.0,  3.0}, {-0.5, 4.0, 3.0 }, {0.5, 4.0,  3.0 }, {3.0, 2.0, 3.0}},

    };
    drawcontrolPoints(controlPointsRoof); 

    GLfloat controlPointsGround[uOrder][vOrder][3] =
    {
     {{-1.5, 0.0, -3.0}, {-0.5, 0.0,-3.0 }, {0.5, 0.0, -3.0 }, {1.5, 0.0,-3.0}},
     {{-1.5, 0.0, -1.0}, {-0.5, 0.0,-1.0 }, {0.5, 0.0, -1.0 }, {1.5, 0.0,-1.0}},
     {{-1.5, 0.0,  1.0}, {-0.5, 0.0, 1.0 }, {0.5, 0.0,  1.0 }, {1.5, 0.0, 1.0}},
     {{-1.5, 0.0,  3.0}, {-0.5, 0.0, 3.0 }, {0.5, 0.0,  3.0 }, {1.5, 0.0, 3.0}}
    };
    drawcontrolPoints(controlPointsGround);

    GLfloat controlPointsSideWall1[uOrder][vOrder][3] =
    {
     {{-3.0, 1.0, -1.5}, {-0.5, 1.0,-1.5 }, {0.5, 1.0, -1.5 }, {3.0, 1.0,-1.5}},
     {{-3.0, 1.0, -0.5}, {-0.5, 1.0,-0.5 }, {0.5, 1.0, -0.5 }, {3.0, 1.0,-0.5}},
     {{-3.0, 1.0,  0.5}, {-0.5, 1.0, 0.5 }, {0.5, 1.0,  0.5 }, {3.0, 1.0, 0.5}},
     {{-3.0, 1.0,  1.5}, {-0.5, 1.0, 1.5 }, {0.5, 1.0,  1.5 }, {3.0, 1.0, 1.5}}
    };
    glRotatef(-120.0, 1.0, 1.0, 1.0);
    glTranslatef(-0.80, 0.0, 1.0);

    drawcontrolPoints(controlPointsSideWall1);

    GLfloat controlPointsSideWall2[uOrder][vOrder][3] =
    {
     {{-3.0, 1.0, -1.5}, {-0.5, 1.0,-1.5 }, {0.5, 1.0, -1.5 }, {3.0, 1.0,-1.5}},
     {{-3.0, 1.0, -0.5}, {-0.5, 1.0,-0.5 }, {0.5, 1.0, -0.5 }, {3.0, 1.0,-0.5}},
     {{-3.0, 1.0,  0.5}, {-0.5, 1.0, 0.5 }, {0.5, 1.0,  0.5 }, {3.0, 1.0, 0.5}},
     {{-3.0, 1.0,  1.5}, {-0.5, 1.0, 1.5 }, {0.5, 1.0,  1.5 }, {3.0, 1.0, 1.5}}
    };
    //glRotatef(0.0, 1.0, 1.0, 1.0);
    glTranslatef(0.0, -3.0, 0.0);
    drawcontrolPoints(controlPointsSideWall2);

    GLfloat controlPointsDoor[uOrder][vOrder][3] =
    {
     {{-1.5, 0.0, -1.5}, {-0.5, 0.0,-1.5 }, {0.5, 0.0, -1.5 }, {1.5, 0.0,-1.5}},
    {{-1.5, 0.0, -0.5}, {-0.5, 0.0,-0.5 }, {0.5, 0.0, -0.5 }, {1.5, 0.0,-0.5}},
    {{-1.5, 0.0,  0.5}, {-0.5, 0.0, 0.5 }, {0.5, 0.0,  0.5 }, {1.5, 0.0, 0.5}},
    {{-1.5, 0.0,  1.5}, {-0.5, 0.0, 1.5 }, {0.5, 0.0,  1.5 }, {1.5, 0.0, 1.5}}
    };
    glRotatef(-120.0, 1.0, 1.0, 1.0);
    glTranslatef(0.0, 3.0, 2.5);
    drawcontrolPoints(controlPointsDoor);

   
    GLfloat controlPointsBackDoor[uOrder][vOrder][3] =
    {
     {{-1.5, 0.0, -1.5}, {-0.5, 0.0,-1.5 }, {0.5, 0.0, -1.5 }, {1.5, 0.0,-1.5}},
    {{-1.5, 0.0, -0.5}, {-0.5, 0.0,-0.5 }, {0.5, 0.0, -0.5 }, {1.5, 0.0,-0.5}},
    {{-1.5, 0.0,  0.5}, {-0.5, 0.0, 0.5 }, {0.5, 0.0,  0.5 }, {1.5, 0.0, 0.5}},
    {{-1.5, 0.0,  1.5}, {-0.5, 0.0, 1.5 }, {0.5, 0.0,  1.5 }, {1.5, 0.0, 1.5}}
    };
    glTranslatef(3.0, -3.0, 3.0);
    drawcontrolPoints(controlPointsBackDoor);
    
       // The following code displays the control points as dots.
       glPointSize( 6.0 );
       glColor3f( 1.0, 0.0, 0.0 );
       glEnable ( GL_POINT_SMOOTH );
       glBegin(GL_POINTS);
       for (i = 0; i < uOrder; i++)
       {
           for (j = 0; j < vOrder; j++)
           {
               glVertex3fv(&controlPointsRoof[i][j][0]);
           }
       }
       glEnd();

       glPointSize(6.0);
       glColor3f(0.0, 1.0, 0.0);
       glEnable(GL_POINT_SMOOTH);
       glBegin(GL_POINTS);
       for (i = 0; i < uOrder; i++)
       {
           for (j = 0; j < vOrder; j++)
           {
               glVertex3fv(&controlPointsGround[i][j][0]);
           }
       }
       glEnd();


       glPointSize(6.0);
       glColor3f(0.0, 0.0, 1.0);
       glEnable(GL_POINT_SMOOTH);
       glBegin(GL_POINTS);
       for (i = 0; i < uOrder; i++)
       {
           for (j = 0; j < vOrder; j++)
           {
               glVertex3fv(&controlPointsSideWall1[i][j][0]);
           }
       }
       glEnd();
    
       glPointSize(6.0);
       glColor3f(0.0, 0.0, 1.0);
       glEnable(GL_POINT_SMOOTH);
       glBegin(GL_POINTS);
       for (i = 0; i < uOrder; i++)
       {
           for (j = 0; j < vOrder; j++)
           {
               glVertex3fv(&controlPointsSideWall2[i][j][0]);
           }
       }
       glEnd();

      


    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
    {
        glOrtho(-5.0, 5.0, -5.0 * (float)h / (float)w,
            5.0 * (float)h / (float)w, 5.0, 25.0);
    }
    else
    {
        glOrtho(-5.0 * (float)w / (float)h,
            5.0 * (float)w / (float)h, -5.0, 5.0, 5.0, 25.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
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
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
