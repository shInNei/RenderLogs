// Sierpinski Gasket Recursion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <gl/glut.h>

constexpr int divideTime = 5;

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*glMatrixMode(GL_MODELVIEW);*/
    glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
}

void Triangle(GLfloat* vertex1, GLfloat* vertex2, GLfloat* vertex3) {
    glVertex2fv(vertex1);
    glVertex2fv(vertex2);
    glVertex2fv(vertex3);
}

void DivideTriangle(GLfloat* vertex1, GLfloat* vertex2, GLfloat* vertex3, int n) {
    GLfloat midPoint1[2], midPoint2[2], midPoint3[2];
    int i;
    if (n > 0) {
        /* Compute midpoint of sides */
        for (i = 0; i < 2; ++i) midPoint1[i] = (vertex1[i] + vertex2[i]) / 2;
        for (i = 0; i < 2; ++i) midPoint2[i] = (vertex1[i] + vertex3[i]) / 2;
        for (i = 0; i < 2; ++i) midPoint3[i] = (vertex2[i] + vertex3[i]) / 2;

        /* subdivide all but inner triangle */
        DivideTriangle(vertex1, midPoint1, midPoint2, n - 1);
        DivideTriangle(vertex2, midPoint1, midPoint3, n - 1);
        DivideTriangle(vertex3, midPoint2, midPoint3, n - 1);
    }
    else Triangle(vertex1, vertex2, vertex3); /* draw triangle at the end of recursion */
}

void myDisplay() {

    // Initialize Triangle
    GLfloat triangleVertex[3][2] = { {-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15} };

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        DivideTriangle(triangleVertex[0], triangleVertex[1], triangleVertex[2], divideTime);
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Sierpinski Gasket using Recursion");

    glutDisplayFunc(myDisplay);
    init();
    glutMainLoop();
    return 0;
}

