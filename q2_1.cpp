#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;
#define VIEWPORT_SIZE 500

class Point
{
public:
    int x;
    int y;
};

vector<Point> points;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, VIEWPORT_SIZE, 0, VIEWPORT_SIZE);
}

void drawLine(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 1.0);
    glPointSize(3.0f);
    glBegin(GL_POINTS);

    for (auto p:points) glVertex2i(p.x, p.y);

    vector<Point> diffs(3);
    vector<int> f(3);
    int x_lbound = points[0].x;
    int x_rbound = x_lbound;
    int y_lbound = points[0].y;
    int y_ubound = y_lbound;

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
    for (int i = 0; i < 3; ++i)
    {
        diffs[i].y = points[(i + 1) % 3].y - points[i].y;
        diffs[i].x = points[(i + 1) % 3].x - points[i].x;
        f[i] = (x_lbound - points[i].x) * diffs[i].y - (y_ubound - points[i].y) * diffs[i].x;
    }
    int A = (points[1].x - points[0].x) * (points[2].y - points[0].y) - 
            (points[1].y - points[0].y) * (points[2].x - points[0].x);
    if (A < 0) A *= -1;
    int q = x_rbound - x_lbound + 1;
    glColor3f(1.0, 0.0, 0.0);

    for (int i = y_ubound; i >= y_lbound; i--)
    {
        for (int j = x_lbound; j <= x_rbound; j++)
        {
            int f1 = (f[0] < 0) || (f[1] < 0) || (f[2] < 0);
            int f2 = (f[0] > 0) || (f[1] > 0) || (f[2] > 0);

            if (!(f1 && f2)) glVertex2i(j, i);
            for (int k = 0; k < 3; ++k) f[k] += diffs[k].y;
        }
        
        for (int k = 0; k < 3; ++k)
        {
            f[k] -= q * diffs[k].y;
            f[k] += diffs[k].x;
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

    for (int i = 0; i < 3; ++i)
    {
        if(points[i].x<10 or points[i].x >= 400){
            cout<<"Point "<<i+1<<" out of bounds";
            return 0;
        };
        if(points[i].y<10 or points[i].y >= 400){
            cout<<"Point "<<i+1<<" out of bounds";
            return 0;
        };
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 30);
    glutInitWindowSize(VIEWPORT_SIZE, VIEWPORT_SIZE);
    glutCreateWindow("Question 2 - Part 1");
    init();
    glutDisplayFunc(drawLine);
    glutMainLoop();
}