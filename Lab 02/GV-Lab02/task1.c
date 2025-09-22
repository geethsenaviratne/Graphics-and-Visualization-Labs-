#include <GLUT/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
        glVertex2i(180, 15);   // Start point
        glVertex2i(10, 145);   // End point
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(0.0, 0.0, 0.0);              // Black line
    gluOrtho2D(0, 200, 0, 200);            // 2D coordinates
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Task 1: Line Segment");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

