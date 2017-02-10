#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include<windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define INF 100000
#define sign(x) ((x > 0)? 1 : ((x < 0)? -1: 0))

/* assignment code starts*/

// Data Structure for holding points


void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

struct PointCoords {
    int x;
    int y;
};

struct Circle
{
    PointCoords center;
    int radius;
};


PointCoords a, b, c;

void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}


int getSlope(PointCoords p1, PointCoords p2)
{
    int slope = (p2.y - p1.y) / (p2.x - p1.x);
    return slope;
}

int getOctant(int slope, PointCoords a, PointCoords b)
{
    int octant = 0;
    
    if(slope >= 0 && slope <= 1 && a.x < b.x) octant = 0;
    else if(slope > 1 && slope < INF && a.y < b.y) octant = 1;
    else if(slope < -1 && slope > -INF && a.y < b.y) octant = 2;
    else if(0 >= slope && slope >= -1 && b.x < a.x) octant = 3;
    else if(0 < slope && slope <= 1 && b.x < a.x) octant = 4;
    else if(1 < slope && slope < INF && b.y < a.y) octant = 5;
    else if(-1 > slope && slope > -INF && b.y < a.y) octant = 6;
    else if(0 >= slope && slope >= -1 && a.x < b.x) octant = 7;
    
    return octant;
}

void mirrorPoints(int octant, int* x1, int* y1, int* x2, int* y2)
{
    switch (octant)
    {
        case 0:
            break;
        case 1:
            swap(x1, y1);
            swap(x2, y2);
            break;
            
        case 2:
            swap(x1, y1);
            *y1 = -(*y1);
            swap(x2, y2);
            *x2 = -(*x2);
            break;
            
        case 3:
            *x1 = -(*x1);
            *x2 = -(*x2);
            break;
            
        case 4:
            *x1 = -(*x1);
            *y1 = -(*y1);
            
            *y2 = -(*y2);
            *x2 = -(*x2);
            break;
            
        case 5:
            swap(x1, y1);
            *y1 = -(*y1);
            *x1 = -(*x1);
            
            swap(x2, y2);
            *x2 = -(*x2);
            *y2 = -(*y2);
            break;
            
        case 6:
            swap(x1, y1);
            *x1 = -(*x1);
            
            swap(x2, y2);
            *y2 = -(*y2);
            break;
            
        case 7:
            *y1 = -(*y1);
            *x2 = -(*x2);
            break;
            
        default:
            break;
    }
}

void drawLine(PointCoords p, PointCoords q)
{
    glColor3f(0, 1, 0);
    int x1,y1,y2,x2;
    
    x1 = p.x, y1 = p.y, x2 = q.x, y2 = q.y;
    
    
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int decisionVar = 2 * dy - dx;
    
    int x = x1;
    int y = y1;
    
    int s1 = sign(x2 - x1), s2 = sign(y2 - y1);
    int s = 0;
    
    int i;
    for(i = 0; i <dx; i++)
    {
        drawPixel(x, y);
        while(decisionVar >= 0)
        {
            decisionVar -= 2 * dx;
            if(s) x += s1;
            else y += s2;
    
        }
    
        decisionVar += 2 * dy;
        if(s) y += s2;
        else x += s1;
    }
    drawPixel(x2, y2);
    
    glFlush();
}


void drawCircle(Circle circle) {
    int x = 0;
    int y = circle.radius;
    
    int decisionVar = 1 - circle.radius;
    
    glColor3f(1, 0, 0);
    
    while(x <= y)
    {
        drawPixel(circle.center.x + x, circle.center.y + y);
        drawPixel(circle.center.x + y, circle.center.y + x);
        drawPixel(circle.center.x - x, circle.center.y + y);
        drawPixel(circle.center.x + y, circle.center.y - x);
        drawPixel(circle.center.x - x, circle.center.y - y);
        drawPixel(circle.center.x - y, circle.center.y - x);
        drawPixel(circle.center.x + x, circle.center.y - y);
        drawPixel(circle.center.x - y, circle.center.y + x);
        
        
        if(decisionVar < 0)
        {
            decisionVar += 2*x + 3;
        }
        else
        {
            decisionVar += ( 2 * ( x - y ) ) + 5;
            y--;
        }
        x++;
    }
    
    glFlush();
}

int getDistance(PointCoords p, PointCoords q)
{
    int distance = 0;
    
    distance = sqrt( pow((q.x - p.x), 2) + pow((q.y - p.y), 2) );
    
    return distance;
}


Circle getCircleData()
{
    PointCoords center;
    
    int l_bc = getDistance(b, c);
    int m_ac = getDistance(a, c);
    int n_ab = getDistance(a, b);
    
    center.x = (a.x * l_bc + b.x * m_ac + c.x * n_ab) / (l_bc + m_ac + n_ab);
    center.y = (a.y * l_bc + b.y * m_ac + c.y * n_ab) / (l_bc + m_ac + n_ab);
    
    int radius = 0.5 + (m_ac + n_ab - l_bc);
    
    Circle c;
    c.center = center;
    c.radius = radius;
    
    return c;
}

/* assignment code ends */

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
    
   
    glPushMatrix();
    drawLine(a, b);
    drawLine(b, c);
    drawLine(c, a);
    glPopMatrix();
    
     Circle c = getCircleData();
    
    
    glPushMatrix();
    
    drawCircle(c);
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

/* Program entry point */

int main(int argc, char *argv[])
{
    int x1, x2, y1, y2, x3, y3;
    printf("Enter values of -> x1 y1 x2 y2 x3 y3 :\n");
    scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
    
    a.x = x1, a.y = y1;
    b.x = x2, b.y = y2;
    c.x = x3, c.y = y3;
    
    
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    
    glutCreateWindow("Assignment # 1");
    
    
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    
    glClearColor(0,0,0,0);
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}
