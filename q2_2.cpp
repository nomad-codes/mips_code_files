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
vector<Point> inPoints;


void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, VIEWPORT_SIZE, 0, VIEWPORT_SIZE);
}

void slopeGreaterUnity(Point p1, Point p2)
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


void drawLine(Point p1, Point p2)
{

    if (abs(p2.y - p1.y) < abs(p2.x - p1.x))
    {
        if (p2.x < p1.x)
            swap(p2.x, p1.x), swap(p2.y, p1.y);
        slope_less_one(p1, p2);
    }
    else
    {
        if (p2.y < p1.y)
            swap(p2.x, p1.x), swap(p2.y, p1.y);
        slopeGreaterUnity(p1, p2);
    }
}

int decideSign(Point a, Point b, int x)
{
    if (x)
    {
        if (b.x - a.x > 0)
            return 1;
        if (b.x - a.x == 0)
            return 0;
        return -1;
    }
    if (b.y - a.y > 0)
        return 1;
    if (b.y - a.y == 0)
        return 0;
    return -1;
}


void draw_hline_trngl(Point p1, Point p2, Point p3)
{
    int c1 = 0, c2 = 0;
    Point temp1 = p1, temp2 = p1;
    Point d1, d2;
    d1.x = abs(p2.x - p1.x);
    d2.x = abs(p3.x - p1.x);
    d1.y = abs(p2.y - p1.y);
    d2.y = abs(p3.y - p1.y);

    if (d1.y > d1.x)
    {
        swap(d1.x, d1.y);
        c1 = true;
    }

    if (d2.y > d2.x)
    {
        swap(d2.x, d2.y);
        c2 = true;
    }

    int signx1 = decideSign(p1, p2, 1), signx2 = decideSign(p1, p3, 1);
    int signy1 = decideSign(p1, p2, 0), signy2 = decideSign(p1, p3, 0);

    int df1 = 2 * d1.y - d1.x;
    int df2 = 2 * d2.y - d2.x;

    for (int i = 0; i <= d1.x; i++)
    {
        drawLine(temp1, temp2);

        while (df1 >= 0)
        {
            if (c1)
                temp1.x += signx1;
            else
                temp1.y += signy1;

            df1 = df1 - 2 * d1.x;
        }

        if (c1)
            temp1.y += signy1;
        else
            temp1.x += signx1;

        df1 += 2 * d1.y;

        while (1)
        {
            if (temp1.y == temp2.y)
                break;
            while (df2 >= 0)
            {
                if (c2 != 0)
                    temp2.x += signx2;
                else
                    temp2.y += signy2;

                df2 = df2 - 2 * d2.x;
            }
            if (c2 != 0)
                temp2.y += signy2;
            else
                temp2.x += signx2;

            df2 += 2 * d2.y;
        }
    }
}

bool cust(const Point a, const Point b)
{
    return a.y < b.y;
}
void displayTriangle()
{

    vector<Point> ip_copy = inPoints;
    sort(ip_copy.begin(), ip_copy.end(), cust);

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    for (auto p : ip_copy)
        glVertex2i(p.x, p.y);
    Point point4;

    if (ip_copy[1].y - ip_copy[2].y == 0)
        draw_hline_trngl(ip_copy[0], ip_copy[1], ip_copy[2]);
    else if (ip_copy[0].y - ip_copy[1].y == 0)
    {
        draw_hline_trngl(ip_copy[2], ip_copy[0], ip_copy[1]);
    }
    else
    {
        point4.y = ip_copy[1].y;
        float z = (float)(ip_copy[1].y - ip_copy[0].y);
        point4.x = (int)((z / (1.0 * ip_copy[2].x - ip_copy[0].x)) * (1.0 * (ip_copy[2].x - ip_copy[0].x)));
        point4.x += ip_copy[0].x;
        draw_hline_trngl(ip_copy[0], ip_copy[1], point4);
        draw_hline_trngl(ip_copy[2], ip_copy[1], point4);
    }
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{

    inPoints.resize(3);
    cout << "Enter x coordinate of point 1: ";
    cin >> inPoints[0].x;
    cout << "Enter y coordinate of point 1: ";
    cin >> inPoints[0].y;
    cout << "Enter x coordinate of point 2: ";
    cin >> inPoints[1].x;
    cout << "Enter y coordinate of point 2: ";
    cin >> inPoints[1].y;
    cout << "Enter x coordinate of point 3: ";
    cin >> inPoints[2].x;
    cout << "Enter y coordinate of point 3: ";
    cin >> inPoints[2].y;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 30);
    glutInitWindowSize(VIEWPORT_SIZE, VIEWPORT_SIZE);
    glutCreateWindow("Question 2 - Part 2");
    init();
    glutDisplayFunc(displayTriangle);
    glutMainLoop();
}