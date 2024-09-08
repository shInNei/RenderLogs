// NationalFlag.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <GL/glut.h>
#include <math.h>

constexpr GLfloat PI = 3.14159265f;

constexpr GLfloat R = 2.0f;

struct Point2D {
	GLfloat x, y;
};

Point2D points[10];

void Init() {
	/* attributes */
	glClearColor(1.0, 0.0, 0.0, 1.0); 
	glColor3f(1.0, 1.0, 0.0); 

	/* set up viewing */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.5, 4.5, -3.0, 3.0, -1.0, 1.0);
}

// Find the pos of Intersection point
Point2D Intersection(Point2D p1, Point2D p2, Point2D p3, Point2D p4) {
	Point2D result;
	GLfloat a1, a2, b1, b2;
	a1 = (p2.y - p1.y) / (p2.x - p1.x);
	b1 = p1.y - a1 * p1.x;

	a2 = (p4.y - p3.y) / (p4.x - p3.x);
	b2 = p3.y - a2 * p3.x;

	result.x = (b2 - b1) / (a1 - a2);
	result.y = a1 * result.x + b1;

	return result;
}

void CalculatePoint() {
	// Calculate the first five points of the star
	// Use circle equation
	for (int i = 0; i < 5; ++i) {
		points[i].x = R * cos(PI / 2 + i * 2 * PI / 5); // 2 pi -> 5 points => 1 point must increase 2/5 pi
		points[i].y = R * sin(PI / 2 + i * 2 * PI / 5);
	}


	// Calculate the last five points of the star
	// Intersection 1st 4 points
	points[5] = Intersection(points[0], points[2], points[1], points[4]);
	points[6] = Intersection(points[0], points[2], points[1], points[3	]);
	points[7] = Intersection(points[1], points[3], points[2], points[4]);
	points[8] = Intersection(points[0], points[3], points[2], points[4]);
	points[9] = Intersection(points[0], points[3], points[1], points[4]);
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	CalculatePoint();
	
	// There are two ways: Triangle fan or 5 triangles + polygon in the middle
	// Can not use Polygon for 10 points => star is concave, not convex
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0, 0.0);
		glVertex2f(points[0].x, points[0].y);
		glVertex2f(points[5].x, points[5].y);
		glVertex2f(points[1].x, points[1].y);
		glVertex2f(points[6].x, points[6].y);
		glVertex2f(points[2].x, points[2].y);
		glVertex2f(points[7].x, points[7].y);
		glVertex2f(points[3].x, points[3].y);
		glVertex2f(points[8].x, points[8].y);
		glVertex2f(points[4].x, points[4].y);
		glVertex2f(points[9].x, points[9].y);
		glVertex2f(points[0].x, points[0].y);
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInitWindowSize(600, 400); //set window size
	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("National Flag");
	glutDisplayFunc(myDisplay);

	Init();
	glutMainLoop();
	return 0;
}
