#include <GL/glut.h>
#include <stdio.h>

int x0 = 20, y0 = 20, x1 = 180, y1 = 80;  // Example endpoints

// Function to plot a point
void plotPixel(int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

// Bresenham algorithm for slope 0 < m < 1
void bresenhamLine(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int p = 2*dy - dx;
    int x = x0, y = y0;

    while (x <= x1) {
        plotPixel(x, y);
        x++;
        if (p < 0) {
            p = p + 2*dy;
        } else {
            y++;
            p = p + 2*dy - 2*dx;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);  // White pixels
    glPointSize(3.0f);

    bresenhamLine(x0, y0, x1, y1);

    glFlush();
}

void init2D() {
    glClearColor(0.0, 0.0, 0.0, 1.0);   // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 200, 0, 200);        // Coordinate system (0 200)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 02 - Task 2: Bresenham Line");

    init2D();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
