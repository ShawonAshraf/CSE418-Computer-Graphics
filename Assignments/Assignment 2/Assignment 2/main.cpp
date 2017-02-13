#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <vector>

/* system function prototypes */
void drawPixel(int x, int y);
static void resize(int width, int height);
static void display(void);
static void key(unsigned char key, int x, int y);
static void idle(void);

/* ds */

struct Point {
    int x;
    int y;
};

std::vector<Point> points;
int numPoints;
const int ROTATE_ANGLE = 0.0;

/* user function prototypes */

void DrawPolygon(std::vector<Point>& points);

/* Program entry point */

int main(int argc, char *argv[])
{
    std::cin >> numPoints;
    for(int i = 0; i < numPoints; i++)
    {
        Point x;
        std::cin >> x.x >> x.y;
        points.push_back(x);
    }
    
    
    glutInit(&argc, argv);
    glutInitWindowSize(1024,768);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    
    glutCreateWindow("assignment 2");
    
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    
    glClearColor(1,1,1,1);
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}


/* system function implementations */


void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glOrtho(-width/2, width/2, -height/2, height/2, -300, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t * 90.0;
    
    
    glPushMatrix();
    
    glRotated(60, 1, 0, 0);
    glRotated(a,0,0,1);
    DrawPolygon(points);
    glPopMatrix();
    
    
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
    }
    
    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

/* user function implementations */


void DrawPolygon(std::vector<Point>& points)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    
    glBegin(GL_POLYGON);
    for (int i = 0; i < numPoints; i++) {
        glVertex2i(points[i].x, points[i].y);
    }
    glEnd();
    glFlush();

}

