// Sierpinski Gasket Recursion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <gl/glut.h>

constexpr int divideTime = 4;

// Initialize colors
GLfloat colors[4][3] = { {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 0.0} };

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
   /* glColor3f(1.0, 0.0, 0.0);*/

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*glMatrixMode(GL_MODELVIEW);*/
    glOrtho(-1, 1, -1, 1, 0.1, 1000);
}

void Triangle(GLfloat* vertex1, GLfloat* vertex2, GLfloat* vertex3) {
    glVertex3fv(vertex1);
    glVertex3fv(vertex2);
    glVertex3fv(vertex3);
}

void Tetrahedron(GLfloat* vertex1, GLfloat* vertex2, GLfloat* vertex3, GLfloat* vertex4) {
    glColor3fv(colors[0]);
    Triangle(vertex2, vertex4, vertex3);
    glColor3fv(colors[1]);
    Triangle(vertex1, vertex2, vertex3);
    glColor3fv(colors[2]);
    Triangle(vertex1, vertex3, vertex4);
    glColor3fv(colors[3]);
    Triangle(vertex1, vertex4, vertex2);
}

void DivideTriangle(GLfloat* vertex1, GLfloat* vertex2, GLfloat* vertex3, GLfloat* vertex4, int n) {
    GLfloat midPoint[6][3];
    int i;
    if (n > 0) {
        /* Compute midpoint of sides */
        for (i = 0; i < 3; ++i) midPoint[0][i] = (vertex1[i] + vertex2[i]) / 2;
        for (i = 0; i < 3; ++i) midPoint[1][i] = (vertex2[i] + vertex3[i]) / 2;
        for (i = 0; i < 3; ++i) midPoint[2][i] = (vertex1[i] + vertex3[i]) / 2;
        for (i = 0; i < 3; ++i) midPoint[3][i] = (vertex1[i] + vertex4[i]) / 2;
        for (i = 0; i < 3; ++i) midPoint[4][i] = (vertex2[i] + vertex4[i]) / 2;
        for (i = 0; i < 3; ++i) midPoint[5][i] = (vertex3[i] + vertex4[i]) / 2;

        /* subdivide all but inner triangle */
        DivideTriangle(vertex1, midPoint[0], midPoint[2], midPoint[3], n - 1);
        DivideTriangle(vertex2, midPoint[0], midPoint[1], midPoint[4], n - 1);
        DivideTriangle(vertex3, midPoint[1], midPoint[2], midPoint[5], n - 1);
        DivideTriangle(vertex4, midPoint[3], midPoint[4], midPoint[5], n - 1);
    }
    else Tetrahedron(vertex1, vertex2, vertex3, vertex4); /* draw triangle at the end of recursion */
}

void myDisplay() {
    // Initialize Tetrahedron
    GLfloat initTetra[4][3] = { {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} };

    glClear(GL_COLOR_BUFFER_BIT);

    // Set Camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-1, -1, -1, 0, 0, 0, 0, 1, 0);

    glBegin(GL_TRIANGLES);
    DivideTriangle(initTetra[0], initTetra[1], initTetra[2], initTetra[3], divideTime);
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Sierpinski Gasket using Recursion");

    glutDisplayFunc(myDisplay);
    init();
    glutMainLoop();
    return 0;
}

