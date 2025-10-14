#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265

void drawCircle(float x, float y, float z, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * PI / 180.0f;
        glVertex3f(x + radius * cos(angle), y + radius * sin(angle), z);
    }
    glEnd();
}

void drawSquare(float x, float y, float z, float size, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex3f(x - size, y - size, z);
    glVertex3f(x + size, y - size, z);
    glVertex3f(x + size, y + size, z);
    glVertex3f(x - size, y + size, z);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    glDisable(GL_DEPTH_TEST);
    
    drawCircle(0.3f, 0.0f, -0.5f, 0.4f, 1.0f, 1.0f, 0.0f); // Yellow circle
    drawCircle(0.0f, 0.2f, -0.3f, 0.4f, 0.5f, 0.0f, 1.0f); // Purple circle
    drawSquare(-0.2f, -0.2f, -0.1f, 0.3f, 1.0f, 0.5f, 0.0f); // Orange square
    
    glColor3f(0.0f, 0.0f, 0.0f); // Black text
    glRasterPos2f(-0.9f, -0.9f);
    const char* text = "Painter's Algorithm: Back to Front rendering";
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Painter's Algorithm Demo");
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); 
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    
    // It draws stuff from back to front: Yellow circle (farthest), Purple circle (middle), Orange square (closest)

    
    glutMainLoop();
    return 0;
}