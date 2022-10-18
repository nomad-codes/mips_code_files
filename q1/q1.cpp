#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;
#define VIEWPORT_SIZE 500

class Point
{
public:
    int x;
    int y;
};
Point p1, p2;
void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, VIEWPORT_SIZE, 0, VIEWPORT_SIZE);
}

void slope_gt_one(Point p1, Point p2)
{
    int x = p1.x, y = p1.y;
    int dir = 1;
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    if (dx < 0)
    {
        dir = -1;
        dx *= -1;
    }
    int delta_e = 2 * dx;
    int d = delta_e - dy;
    int delta_ne = 2 * (dx - dy);

    glVertex2i(x, y);

    while (y <= p2.y)
    {

        if (d <= 0)
            d = d + delta_e;
        else
        {
            d = d + delta_ne;
            x += dir;
        }

        y++;
        glVertex2i(x, y);
    }
}

void slope_less_one(Point p1, Point p2)
{
    int x = p1.x, y = p1.y;
    int dir = 1;
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    if (dy < 0)
        dir = -1, dy = -dy;

    int delta_e = 2 * dy;
    int d = delta_e - dx;
    int delta_ne = 2 * (dy - dx);

    glVertex2i(x, y);

    while (x <= p2.x)
    {
        if (d <= 0)
        {
            d = d + delta_e;
        }
        else
        {
            d = d + delta_ne;
            y += dir;
        }
        x++;
        glVertex2i(x, y);
    }
}

void pointsToPlot(Point p1, Point p2)
{
    float lineSlope = abs(p2.y - p1.y) * 1.0 / abs(p2.x - p1.x);
    if (lineSlope < 1)
    {
        if (p2.x < p1.x)
            swap(p2.x, p1.x), swap(p2.y, p1.y);
        slope_less_one(p1, p2);
        return;
    }

    if (p2.y < p1.y)
    {
        swap(p2.x, p1.x);
        swap(p2.y, p1.y);
    }
    slope_gt_one(p1, p2);
}

void drawLine()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glPointSize(4.0f);
    glBegin(GL_POINTS);
    glVertex2i(p1.x, p1.y);
    glVertex2i(p2.x, p2.y);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    pointsToPlot(p1, p2);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    printf("Enter p1-x: ");
    cin >> p1.x;
    printf("Enter p1-y: ");
    cin >> p1.y;
    printf("Enter p2-x: ");
    cin >> p2.x;
    printf("Enter p2-y: ");
    cin >> p2.y;

    if (p1.x < 30 or p1.x > 400 or p2.x < 30 or p2.x > 400)
    {
        printf("Points out of constraint bounds\n");
        return 0;
    }
    if (p2.y < 30 or p2.y > 400 or p2.y < 30 or p2.y > 400)
    {
        printf("Points out of constraint bounds\n");
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 30);
    glutInitWindowSize(VIEWPORT_SIZE, VIEWPORT_SIZE);
    glutCreateWindow("Question 1");
    init();
    glutDisplayFunc(drawLine);
    glutMainLoop();
}