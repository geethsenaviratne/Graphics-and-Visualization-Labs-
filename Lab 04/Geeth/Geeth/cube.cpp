#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>

void createCube() {
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    
    // Back face (Green)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.2, 0.0, -0.4);
    glVertex3f(-0.2, 0.4, -0.4);
    glVertex3f(0.2, 0.4, -0.4);
    glVertex3f(0.2, 0.0, -0.4);
    glEnd();
    
    // Left face (Blue)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.4, -0.2, 0.0);
    glVertex3f(-0.4, 0.2, 0.0);
    glVertex3f(-0.2, 0.4, -0.4);
    glVertex3f(-0.2, 0.0, -0.4);
    glEnd();
    
    // Right face (Blue)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, -0.2, 0.0);
    glVertex3f(0.0, 0.2, 0.0);
    glVertex3f(0.2, 0.4, -0.4);
    glVertex3f(0.2, 0.0, -0.4);
    glEnd();
    
    // Top face (White)
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.4, 0.2, 0.0);
    glVertex3f(0.0, 0.2, 0.0);
    glVertex3f(0.2, 0.4, -0.4);
    glVertex3f(-0.2, 0.4, -0.4);
    glEnd();
    
    // Bottom face (Yellow)
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.4, -0.2, 0.0);
    glVertex3f(0.0, -0.2, 0.0);
    glVertex3f(0.2, 0.0, -0.4);
    glVertex3f(-0.2, 0.0, -0.4);
    glEnd();

    // Front face (Red)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.4, -0.2, 0.0);
    glVertex3f(-0.4, 0.2, 0.0);
    glVertex3f(0.0, 0.2, 0.0);
    glVertex3f(0.0, -0.2, 0.0);
    glEnd();

    glFlush(); // Render the scene
}

void display(void) {
    createCube();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(500, 500);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cube of IT23226128");

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}