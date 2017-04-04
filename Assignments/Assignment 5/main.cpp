// Assignment 5.cpp : Defines the entry point for the console application.
//

#ifdef __APPLE__

#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#endif

#include <cstdlib>

/* system function prototypes */
void drawPixel(int x, int y);

static void resize(int width, int height);

static void display(void);

static void key(unsigned char key, int x, int y);

static void idle(void);

/* user function prototypes */

void drawCube();

/* Program entry point */

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("Assignment 5");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0, 0, 0, 0);

    glutMainLoop();

    return 0;
}


/* system function implementations */


void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

/* GLUT callback Handlers */

static void resize(int width, int height) {
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(40.0, (GLdouble) width / (GLdouble) height, 0.5, 20.0);
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
//    glOrtho(-width / 2, width / 2, -height / 2, height / 2, -300, 300);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, width, height);
//    glLoadIdentity();
}

static void display(void) {

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    drawCube();
    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
        case 'q':
            exit(0);
    }

    glutPostRedisplay();
}

static void idle(void) {
    glutPostRedisplay();
}


/* user function implementations */

void drawCube() {

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.5);

    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

    glFlush();
}
