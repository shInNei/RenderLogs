// Sierpinski Gasket.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <GL/glut.h>
#include <cstdlib>


void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-11.0, 11.0, -1.0, 9.0, -1.0, 1.0);
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3.0);
    // Initialize Triangle
    GLfloat triangleVertex[3][2] = { { -10.0, 0.0}, { 0.0, 8.0} , {6.5, 0.0} };
    
    // Random Initial Point inside the Triangle
    // Triangle Centroid
    GLfloat initPoint[2];
    initPoint[0] = (triangleVertex[0][0] + triangleVertex[1][0] + triangleVertex[2][0]) / 3;
    initPoint[1] = (triangleVertex[0][1] + triangleVertex[1][1] + triangleVertex[2][1]) / 3;

    glBegin(GL_POINTS);
        for (int i = 0, j = 0; i < 5000; ++i) {
            j = rand() % 3;
            initPoint[0] = (initPoint[0] + triangleVertex[j][0]) / 2;
            initPoint[1] = (initPoint[1] + triangleVertex[j][1]) / 2;
            glVertex2f(initPoint[0], initPoint[1]);
        }
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1100, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Sierpinski Gasket");

    glutDisplayFunc(myDisplay);
    init();
    glutMainLoop();
    return 0;
}

