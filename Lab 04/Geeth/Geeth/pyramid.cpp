#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>

void createPyramid() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Base (Square - using two triangles)
    glColor3f(0.5, 0.5, 0.5);
    
    // First triangle of base
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, 0.0, -0.5);
    glVertex3f(0.5, 0.0, -0.5);
    glVertex3f(-0.5, 0.0, 0.5);
    glEnd();
    
    // Second triangle of base
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5, 0.0, -0.5);
    glVertex3f(0.5, 0.0, 0.5);
    glVertex3f(-0.5, 0.0, 0.5);
    glEnd();
    
    // Front face (Red)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, 0.0, -0.5);
    glVertex3f(0.5, 0.0, -0.5);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    
    // Right face (Green)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5, 0.0, -0.5);
    glVertex3f(0.5, 0.0, 0.5);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    
    // Back face (Blue)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5, 0.0, 0.5);
    glVertex3f(-0.5, 0.0, 0.5);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    
    // Left face (Yellow)
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, 0.0, 0.5);
    glVertex3f(-0.5, 0.0, -0.5);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    
    glFlush();
}

void display(void) {
    createPyramid();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'r': case 'R':
            glRotatef(10.0, 0.0, 1.0, 0.0); // Rotate around Y-axis
            break;
        case 'x': case 'X':
            glRotatef(10.0, 1.0, 0.0, 0.0); // Rotate around X-axis
            break;
        case 'q': case 'Q':
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Pyramid - IT12345678");  // Replace with your IT index
    
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}