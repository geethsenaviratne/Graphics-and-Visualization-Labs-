#include <GL/glut.h>
#include <stdio.h>

float angle = 0.0f;
int showBackface = 1; // 1 = show backface, 0 = cull backface

void drawColoredCube(float size) {
    float s = size * 0.5f;
    glBegin(GL_QUADS);
    // +Z (front) - RED
    glColor3f(1, 0, 0);
    glVertex3f(-s, -s,  s);
    glVertex3f( s, -s,  s);
    glVertex3f( s,  s,  s);
    glVertex3f(-s,  s,  s);
    // -Z (back) - GREEN
    glColor3f(0, 1, 0);
    glVertex3f( s, -s, -s);
    glVertex3f(-s, -s, -s);
    glVertex3f(-s,  s, -s);
    glVertex3f( s,  s, -s);
    // +Y (top) - BLUE
    glColor3f(0, 0, 1);
    glVertex3f(-s,  s,  s);
    glVertex3f( s,  s,  s);
    glVertex3f( s,  s, -s);
    glVertex3f(-s,  s, -s);
    // -Y (bottom) - YELLOW
    glColor3f(1, 1, 0);
    glVertex3f(-s, -s, -s);
    glVertex3f( s, -s, -s);
    glVertex3f( s, -s,  s);
    glVertex3f(-s, -s,  s);
    // +X (right) - MAGENTA
    glColor3f(1, 0, 1);
    glVertex3f( s, -s,  s);
    glVertex3f( s, -s, -s);
    glVertex3f( s,  s, -s);
    glVertex3f( s,  s,  s);
    // -X (left) - CYAN
    glColor3f(0, 1, 1);
    glVertex3f(-s, -s, -s);
    glVertex3f(-s, -s,  s);
    glVertex3f(-s,  s,  s);
    glVertex3f(-s,  s, -s);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
    glRotatef(40, 0, 0, 1);
    glRotatef(30, 1, 0, 0);
    glRotatef(angle, 0, 1, 0);

    if (showBackface) {
        glDisable(GL_CULL_FACE);
    } else {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    drawColoredCube(1.2f);
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        showBackface = !showBackface;
        printf("Back-face culling: %s\n", showBackface ? "DISABLED" : "ENABLED");
    }
    glutPostRedisplay();
}

void idle() {
    angle += 0.05f;
    if (angle >= 360.0f) angle -= 360.0f;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Back-Face Culling Demo - Press SPACE to toggle");

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);   // set default face winding
    glClearColor(0.12f, 0.12f, 0.12f, 1.0f);

    printf("Press SPACE to toggle back-face culling\n");
    printf("Initial state: Back-face culling DISABLED (you see both sides)\n");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}