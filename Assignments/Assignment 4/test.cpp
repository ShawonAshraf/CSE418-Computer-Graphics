//
// Created by shawonashraf on 3/22/17.
//

#include <GL/glut.h>
#include <stdio.h>

struct  V
{
    int x,y,z;
    float SlopeX , SlopeY , SlopeZ;
} ;
int NVerticesPlus1,NVertices;
struct V Vertex[100];
int i;
float H0(float u)
{
    return(2*u*u*u - 3*u*u + 1);
}
float H1(float u)
{
    return(-2*u*u*u + 3*u*u );
}
float H2(float u)
{
    return(u*u*u - 2*u*u + u);
}
float H3(float u)
{
    return(u*u*u - u*u );
}
void display(void)
{
    glClear (GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);
// Set the color to BLACK
    glBegin(GL_LINES);
    // Plotting X-Axis
    glVertex3f(-1000 ,0 , 0);
    glVertex3f( 1000 ,0 , 0);
    glEnd();
    glBegin(GL_LINES);                                                                                  // Plotting Y-Axis
    glVertex3f(0 ,-1000 , 0);
    glVertex3f(0 , 1000 , 0);
    glEnd();
    glColor3f (0.5, 0.5, 1.0);
    NVertices = NVerticesPlus1 - 1;
    float u ;
    float x,y,z;
    glLineWidth( 3 ); // Lines are n pixels wide
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Antialias lines
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_LINE_STRIP);
    for(i=0 ; i<NVertices ; i++)
    {
        for(u = 0 ; u<=1 ; u+=0.04)
        {
            x = Vertex[i].x * H0(u) + Vertex[i+1].x * H1(u) +
                Vertex[i].SlopeX * H2(u) + Vertex[i+1].SlopeX * H3(u);
            y = Vertex[i].y * H0(u) + Vertex[i+1].y * H1(u) +
                Vertex[i].SlopeY * H2(u) + Vertex[i+1].SlopeY * H3(u);
            z = Vertex[i].z * H0(u) + Vertex[i+1].z * H1(u) +
                Vertex[i].SlopeZ * H2(u) + Vertex[i+1].SlopeZ * H3(u);
            glVertex3f(x,y,z);
        }
    }
    glEnd();
    glColor3f (0.0, 0.0, 0.0);
    glPointSize(6);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_POINTS);
    for(i=0 ; i<NVerticesPlus1 ; i++)
        glVertex3f(Vertex[i].x , Vertex[i].y , Vertex[i].z);
    glEnd();
    glFlush();
}
void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
    glEnable(GL_DEPTH_TEST);
}
int main (int argc, char *argv)
{
    glutInit(&argc, &argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (900,800);
    glutInitWindowPosition (0, 0);
    glutCreateWindow (" Hermite Interpolation ");
    init ();
    printf("Enter the no. of Vertices of Curve:\n=> ");
    scanf("%d",&NVerticesPlus1);
    for(i=0 ; i<NVerticesPlus1 ; i++)
    {
        printf("Enter %dth vertex x , y & z Co-ordinates\n",i+1);
        scanf("%d%d%d",&Vertex[i].x , &Vertex[i].y , &Vertex[i].z);
        printf("Enter %dth vertex x , y & z slopes :\n",i+1);
        scanf("%f%f%f",&Vertex[i].SlopeX,&Vertex[i].SlopeY,&Vertex[i].SlopeZ);
    }
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

