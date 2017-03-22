#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include <stdio.h>


/* system function prototypes */
void drawPixel(int x, int y);

static void resize(int width, int height);

static void display(void);

static void key(unsigned char key, int x, int y);

static void idle(void);

/* user function prototypes */
void drawPixel3D(double x, double y, double z);

double GetHermiteEndPoint_01(int t);

double GetHermiteEndPoint_02(int t);

double GetSlopeHermite_01(int t);

double GetSlopeHermite_02(int t);

void DrawHermite();

/* Global vars */


struct EndPoint {
    int x;
    int y;
    int z;
    double slopeX;
    double slopeY;
    double slopeZ;
};

EndPoint P1, P4;

/* Program entry point */

int main(int argc, char *argv[]) {

    printf("Enter X, Y, Z for P1 : ");
    scanf("%d %d %d", &P1.x, &P1.y, &P1.z);

    printf("Enter X, Y, Z for P4 : ");
    scanf("%d %d %d", &P4.x, &P4.y, &P4.z);

    printf("Slope Vector for P1 : ");
    scanf("%lf %lf %lf", &P1.slopeX, &P1.slopeY, &P1.slopeZ);

    printf("Slope Vector for P4 : ");
    scanf("%lf %lf %lf", &P4.slopeX, &P4.slopeY, &P4.slopeZ);


    glutInit(&argc, argv);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("Assignment 4");

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
//    glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1000, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void) {
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0, 1, 0);

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t * 90.0;

    glPushMatrix();
    glRotated(60, 1, 0, 0);
    glRotated(a, 0, 1, 0);
    DrawHermite();
    glPopMatrix();

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
void drawPixel3D(double x, double y, double z) {
    glBegin(GL_POINT);
    glVertex3d(x, y, z);
    glEnd();

    glFlush();
}

double GetHermiteEndPoint_01(int t) {
    double h0 = (2 * t * t * t - 3 * t * t + 1);
    return h0;

}

double GetHermiteEndPoint_02(int t) {
    double h1 = (-2 * t * t * t + 3 * t * t);
    return h1;
}


double GetSlopeHermite_01(int t) {
    double h3 = (t * t * t - 2 * t * t + t);
    return h3;
}

double GetSlopeHermite_02(int t) {
    double h4 = (t * t * t - t * t);
    return h4;
}

void DrawHermite() {
    int n = 100;

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < n; i++) {
        for (double t = 0; t <= 10; t += 0.1) {
            double h0 = GetHermiteEndPoint_01(t);
            double h1 = GetHermiteEndPoint_02(t);
            double h3 = GetSlopeHermite_01(t);
            double h4 = GetSlopeHermite_02(t);

            double x, y, z;

            x += P1.x * h0 + P1.slopeX * h3
                 + P4.slopeX * h4 + P4.x * h1;

            y += P1.y * h0 + P1.slopeY * h3
                 + P4.y * h1 + P4.slopeY;

            z += P1.z * h0 + P1.slopeZ * h3
                 + P4.z * h1 + P4.slopeZ;

            glVertex3d(x, y, z);
        }
    }
    glEnd();


    glFlush();
}
