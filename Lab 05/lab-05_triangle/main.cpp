#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
// Function to draw a simple triangle
void drawTriangle(void) {
// Set color to red (RGB values between 0.0 and 1.0)
    glColor3f(1.0, 0.0, 0.0);

    // Begin drawing triangles
    glBegin(GL_TRIANGLES);

    // Define three vertices to form a triangle
    // Bottom left vertex
    glVertex2f(-0.2, -0.2);
    // Bottom right vertex
    glVertex2f(0.2, -0.2);
    // Top vertex
    glVertex2f(0.0, 0.2);

    // End drawing
    glEnd();
}

// Translation transformation example
void Translate() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw original triangle
    glColor3f(1.0, 0.0, 0.0); // Red
    drawTriangle();

    // Apply translation transformation
    // Save current transformation matrix
    glPushMatrix();

    // Translate by (0.5, 0.3, 0.0)
    glTranslatef(0.5, 0.3, 0.0);

    // Draw translated triangle in blue
    glColor3f(0.0, 0.0, 1.0);
    drawTriangle();

    // Restore previous transformation matrix
    glPopMatrix();

    glutSwapBuffers();
}

// Scaling transformation about origin
void ScaleAboutOrigin() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the original triangle first for reference
    glColor3f(1.0, 0.0, 0.0); // Red
    drawTriangle();

    // Apply scaling transformation about origin
    glPushMatrix();
    // Scale by 2.0 in X, 1.5 in Y, 1.0 in Z
    glScalef(2.0, 1.5, 1.0);

    // Draw scaled triangle in blue
    glColor3f(0.0, 0.0, 1.0);
    drawTriangle();
    glPopMatrix();

    glFlush();
}

// Scaling transformation about a fixed point
void ScaleAboutFixedPoint() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the original triangle first for reference
    glColor3f(1.0, 0.0, 0.0); // Red
    drawTriangle();

    // Implement scaling about a fixed point (0.25, 0.25)
    // Strategy: Move fixed point to origin, scale, then move back
    glPushMatrix();

    // Move fixed point to origin
    glTranslatef(0.25, 0.25, 0.0);
    // Apply scaling
    glScalef(2.0, 1.5, 1.0);
    // Move back to original position
    glTranslatef(-0.25, -0.25, 0.0);

    // Draw scaled triangle in green
    glColor3f(0.0, 1.0, 0.0);
    drawTriangle();
    glPopMatrix();

    glFlush();
}

// Rotation transformation about origin
void RotationAboutOrigin() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the original triangle first for reference
    glColor3f(1.0, 0.0, 0.0); // Red
    drawTriangle();

    // Apply rotation transformation about origin
    glPushMatrix();
    // Rotate 45 degrees around Z-axis
    glRotatef(45.0, 0.0, 0.0, 1.0);

    // Draw rotated triangle in blue
    glColor3f(0.0, 0.0, 1.0);
    drawTriangle();
    glPopMatrix();

    glFlush();
}

// Rotation about a fixed point (e.g., first vertex)
void RotationAboutFixedPoint() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the original triangle first for reference
    glColor3f(1.0, 0.0, 0.0); // Red
    drawTriangle();

    // Implement rotation about a fixed point (0.0, 0.0)
    // Strategy: Move fixed point to origin, rotate, then move back
    glPushMatrix();

    // Move fixed point to origin (in this case it's already at origin)
    glTranslatef(0.0, 0.0, 0.0);
    // Rotate 45 degrees around Z-axis
    glRotatef(45.0, 0.0, 0.0, 1.0);
    // Move back to original position
    glTranslatef(0.0, 0.0, 0.0);

    // Draw rotated triangle in green
    glColor3f(0.0, 1.0, 0.0);
    drawTriangle();
    glPopMatrix();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0); // 2D orthographic projection
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Basic Transformations");

    init();

    // Uncomment the function you want to test:
    glutDisplayFunc(Translate);
    // glutDisplayFunc(ScaleAboutOrigin);
    // glutDisplayFunc(ScaleAboutFixedPoint);
    // glutDisplayFunc(RotationAboutOrigin);
    // glutDisplayFunc(RotationAboutFixedPoint);

    // Enter the main event loop
    glutMainLoop();
    return 0;
}
