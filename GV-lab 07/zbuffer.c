#include <GL/glut.h>
#include <stdio.h>

int useZBuffer = 1; // Toggle Z-buffer on/off

void drawSquare(float x, float y, float z, float size, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex3f(x - size, y - size, z);
    glVertex3f(x + size, y - size, z);
    glVertex3f(x + size, y + size, z);
    glVertex3f(x - size, y + size, z);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Toggle depth testing based on user input
    if (useZBuffer) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
    
    // Draw in RANDOM order to demonstrate Z-buffer capability
    // Without Z-buffer: render order matters
    // With Z-buffer: Z-values determine visibility
    
    // Draw GREEN square CLOSE (z = -0.3)
    drawSquare(0.2f, 0.2f, -0.3f, 0.3f, 0.0f, 1.0f, 0.0f);
    
    // Draw RED square FAR away (z = -0.8)
    drawSquare(-0.2f, -0.2f, -0.8f, 0.4f, 1.0f, 0.0f, 0.0f);
    
    // Draw BLUE square MIDDLE (z = -0.5)
    drawSquare(0.0f, 0.0f, -0.5f, 0.35f, 0.0f, 0.0f, 1.0f);
    
    // Display status
    glDisable(GL_DEPTH_TEST);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.95f, 0.9f);
    const char* status = useZBuffer ? "Z-Buffer: ENABLED (correct depth)" : "Z-Buffer: DISABLED (render order)";
    for (const char* c = status; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    
    glRasterPos2f(-0.95f, 0.82f);
    const char* instruction = "Press SPACE to toggle Z-buffer";
    for (const char* c = instruction; *c != '\0'; c++) {
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

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        useZBuffer = !useZBuffer;
        printf("Z-Buffer: %s\n", useZBuffer ? "ENABLED" : "DISABLED");
        glutPostRedisplay();
    }

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Z-Buffer Demo");
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    printf("Z-Buffer Demonstration\n");
    printf("Squares drawn in random order:\n");
    // Green (z=-0.3, closest)
    // Red (z=-0.8, farthest)
    // Blue (z=-0.5, middle)
    printf("\nPress SPACE to toggle Z-buffer on/off\n");

    printf("\nWith Z-buffer: Correct depth-based visibility\n");
    printf("Without Z-buffer: Last drawn appears on top\n");
    
    glutMainLoop();
    return 0;
}