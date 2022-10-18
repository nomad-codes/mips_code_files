#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;
#define VIEWPORT_SIZE 500

class Point
{
public:
	float x;
	float y;
};

vector<Point> points;
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, VIEWPORT_SIZE, 0, VIEWPORT_SIZE);
}

void dispSupersampleTriangle()
{

	float x_lbound = points[0].x;
	float x_rbound = x_lbound;
	float y_lbound = points[0].y;
	float y_ubound = y_lbound;

	for (int i = 1; i < 3; i++)
	{
		if (points[i].x < x_lbound)
			x_lbound = points[i].x;
		if (points[i].x > x_rbound)
			x_rbound = points[i].x;
		if (points[i].y < y_lbound)
			y_lbound = points[i].y;
		if (points[i].y > y_ubound)
			y_ubound = points[i].y;
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0f);
	glBegin(GL_POINTS);

	for(auto p:points) glVertex2i(p.x, p.y);

	for (int i = 0; i < 3; i++)
	{
		points[i].x = 2.0 * points[i].x + 0.5 * (2.0 - 1);
		points[i].y = 2.0 * points[i].y + 0.5 * (2.0 - 1);
	}

	vector<Point> diffs(3);
	for (int i = 0; i < 3; ++i)
	{
		diffs[i].x = points[(i + 1) % 3].x - points[i].x;
		diffs[i].y = points[(i + 1) % 3].y - points[i].y;
	}

	float ar = 4.0;
	for (int i = y_ubound; i >= y_lbound; i-=1)
	{
		for (int j = x_lbound; j <= x_rbound; j+=1)
		{

			float cnt = 0, clrg = 0, clrb = 0;
			for (int subsmpl = 0; subsmpl < 2; subsmpl++)
			{
				int xsub = 2.0 * j + 0;
				int ysub = 2.0 * i + 0;

				float f0 = (float)(xsub - points[0].x) * diffs[0].y - (float)(ysub - points[0].y) * diffs[0].x;
				float f1 = (float)(xsub - points[1].x) * diffs[1].y - (float)(ysub - points[1].y) * diffs[1].x;
				float f2 = (float)(xsub - points[2].x) * diffs[2].y - (float)(ysub - points[2].y) * diffs[2].x;

				int flag1 = (f0 < 0) || (f1 < 0) || (f2 < 0);
				int flag2 = (f0 > 0) || (f1 > 0) || (f2 > 0);

				if (!(flag1 && flag2))
					cnt++;
				xsub = 2.0 * j + 1;
				ysub = 2.0 * i + 1;

				f0 = (float)(xsub - points[0].x) * diffs[0].y - (float)(ysub - points[0].y) * diffs[0].x;
				f1 = (float)(xsub - points[1].x) * diffs[1].y - (float)(ysub - points[1].y) * diffs[1].x;
				f2 = (float)(xsub - points[2].x) * diffs[2].y - (float)(ysub - points[2].y) * diffs[2].x;

				flag1 = (f0 < 0) || (f1 < 0) || (f2 < 0);
				flag2 = (f0 > 0) || (f1 > 0) || (f2 > 0);

				if (!(flag1 && flag2))
					cnt++;
			}
			glColor3f(1, (4.0 - cnt) / ar, (ar - cnt) / ar);
			glVertex2i(j, i);
		}
	}

	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{

	points.resize(3);
	cout << "Enter x coordinate of point 1: ";
	cin >> points[0].x;
	cout << "Enter y coordinate of point 1: ";
	cin >> points[0].y;
	cout << "Enter x coordinate of point 2: ";
	cin >> points[1].x;
	cout << "Enter y coordinate of point 2: ";
	cin >> points[1].y;
	cout << "Enter x coordinate of point 3: ";
	cin >> points[2].x;
	cout << "Enter y coordinate of point 3: ";
	cin >> points[2].y;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(10, 30);
	glutInitWindowSize(VIEWPORT_SIZE, VIEWPORT_SIZE);
	glutCreateWindow("Question 2 - Part 3");
	init();
	glutDisplayFunc(dispSupersampleTriangle);
	glutMainLoop();
}