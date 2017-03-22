#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

/* system function prototypes */
void drawPixel(int x, int y);

static void resize(int width, int height);

static void display(void);

static void key(unsigned char key, int x, int y);

static void idle(void);

/* user function prototypes */
void drawPixel3D(int x, int y, int z);

double GetHermiteEndPoint_01(int t);

double GetHermiteEndPoint_02(int t);

/* Global vars */

struct EndPoint {
    int x;
    int y;
    int z;
    double slope;
};

EndPoint P1, P4;

/* Program entry point */

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0, 0, 0, 0);

    glutMainLoop();

    return EXIT_SUCCESS;
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
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glOrtho(-width / 2, width / 2, -height / 2, height / 2, -300, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void) {
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 1, 1);

    glPushMatrix();
    glPopMatrix();
    glFlush();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y) {
    switch (key) {
        case 27 :
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

static void idle(void) {
    glutPostRedisplay();
}

/* user function implementations */
void drawPixel3D(int x, int y, int z) {
    glBegin(GL_POINT);
    glVertex3i(x, y, z);
    glEnd();
}

double GetHermiteEndPoint_01(int t) {
    double h0 = (2 * t * t * t - 3 * t * t + 1) * (P1.x + P1.y + P1.z);
    return h0;

}

double GetHermiteEndPoint_02(int t) {
    double h1 = (-2 * t * t * t + 3 * t * t) * (P4.x + P4.y + P4.z);
    return h1;
}