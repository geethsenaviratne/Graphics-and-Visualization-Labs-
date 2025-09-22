#include <GLUT/glut.h>
#include <stdio.h>

// Function to plot 8 symmetric points of the circle
void plotCirclePoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
    glEnd();
}

// Midpoint Circle Drawing Algorithm
void midpointCircle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 1 - r;  // Initial decision parameter

    plotCirclePoints(xc, yc, x, y);

    while (x < y) {
        x++;
        if (d < 0) {
            d += 2 * x + 1;
        } else {
            y--;
            d += 2 * (x - y) + 1;
        }
        plotCirclePoints(xc, yc, x, y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Example circle center and radius
    int xc = 150, yc = 150, r = 100;
    midpointCircle(xc, yc, r);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White background
    glColor3f(0.0, 0.0, 0.0);          // Black points
    gluOrtho2D(0, 400, 0, 400);        // Define coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Midpoint Circle Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

