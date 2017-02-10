//
//  main.cpp
//  Bresenham Line Drawing
//
//  Created by Shawon Ashraf on 2/10/17.
//  Copyright © 2017 Shawon Ashraf. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <utility>

#define INF 1000000

/* system function prototypes */
void drawPixel(int x, int y);
static void resize(int width, int height);
static void display(void);
static void key(unsigned char key, int x, int y);
static void idle(void);

/* Data Structure for holding a point */
struct Point {
    int x;
    int y;
};

// global vars for points

Point a, b, c;

/* user function prototypes */

void drawLine(Point point1, Point point2);

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    
    glutCreateWindow("GLUT Shapes");
    
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    
    glClearColor(0,0,0,0);
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}


/* system function implementations */


void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
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
    int i;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    
    
    // point data
    a.x = 50; a.y = 100;
    b.x = 0; b.y = -78;
    
    
    glPushMatrix();
    drawLine(a, b);
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

void drawLine(Point point1, Point point2)
{
    glColor3f(0, 1, 1);
    
    int dx = abs(point2.x - point1.x);
    int dy = abs(point2.y - point1.y);
    
    // if number is positive 1, -1 if negative, 0 if 0
    auto sign = [](int number)
    {
        return (number > 0)? 1 : (number < 0)? 1 : 0;
    };
    
    
    int stepX = sign(point2.x - point1.x);
    int stepY = sign(point2.y - point1.y);
    

    int swapNo = 0; // since no swap has occurred for now
    int x = point1.x, y = point1.y;
    
    drawPixel(x, y);
    
    if(dy > dx)
    {
        std::swap(dx, dy);
        swapNo = 1;
    }
    int decisionVar = (dy << 1) - dx;
    
    for(int i = 0; i < dx; i++)
    {
//        drawPixel(x, y);
        while(decisionVar >= 0)
        {
            decisionVar -= 2 * dx;
            if(swapNo) x += stepX;
            else y += stepY;
        }
        
        decisionVar += 2 * dy;
        if(swapNo) y += stepY;
        else x += stepX;
        
        drawPixel(x, y);
    }
}

