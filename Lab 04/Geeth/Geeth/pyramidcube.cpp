// macOS build: use GLUT framework + silence deprecation warnings
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdlib.h>

static const float APEX_PUSH_X = 0.40f; // how far the pyramid apex extends to the right (+X)

// --- one-time init ---
static void init(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0);
}

// --- simple orthographic projection covering our coords ---
static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0,   -1.0, 1.0,   -1.0, 1.0); // z in [-1,1]
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ===== CUBE (same layout as yours, BUT we skip drawing the right face) =====

    // Back face (Green)  z = -0.4
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.2f, 0.0f, -0.4f);
        glVertex3f(-0.2f, 0.4f, -0.4f);
        glVertex3f( 0.2f, 0.4f, -0.4f);
        glVertex3f( 0.2f, 0.0f, -0.4f);
    glEnd();

    // Left face (Blue)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.4f, -0.2f,  0.0f);
        glVertex3f(-0.4f,  0.2f,  0.0f);
        glVertex3f(-0.2f,  0.4f, -0.4f);
        glVertex3f(-0.2f,  0.0f, -0.4f);
    glEnd();

    // Top face (White)
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.4f, 0.2f,  0.0f);
        glVertex3f( 0.0f, 0.2f,  0.0f);
        glVertex3f( 0.2f, 0.4f, -0.4f);
        glVertex3f(-0.2f, 0.4f, -0.4f);
    glEnd();

    // Bottom face (Yellow)
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.4f, -0.2f,  0.0f);
        glVertex3f( 0.0f, -0.2f,  0.0f);
        glVertex3f( 0.2f,  0.0f, -0.4f);
        glVertex3f(-0.2f,  0.0f, -0.4f);
    glEnd();

    // Front face (Red)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.4f, -0.2f, 0.0f);
        glVertex3f(-0.4f,  0.2f, 0.0f);
        glVertex3f( 0.0f,  0.2f, 0.0f);
        glVertex3f( 0.0f, -0.2f, 0.0f);
    glEnd();

    // ===== PYRAMID attached to the RIGHT side =====
    // Base = the quad that was the cube's right face (we don't draw the base itself)
    const GLfloat B1[3] = { 0.0f, -0.2f,  0.0f };  // front-bottom-right
    const GLfloat B2[3] = { 0.0f,  0.2f,  0.0f };  // front-top-right
    const GLfloat B3[3] = { 0.2f,  0.4f, -0.4f };  // back-top-right
    const GLfloat B4[3] = { 0.2f,  0.0f, -0.4f };  // back-bottom-right

    // Centroid of the base (approx center of right face)
    const float cx = (B1[0] + B2[0] + B3[0] + B4[0]) * 0.25f; // ~0.1
    const float cy = (B1[1] + B2[1] + B3[1] + B4[1]) * 0.25f; // ~0.1
    const float cz = (B1[2] + B2[2] + B3[2] + B4[2]) * 0.25f; // ~-0.2

    // Apex pushed outward along +X (to the "right")
    const GLfloat A[3] = { cx + APEX_PUSH_X, cy, cz };

    // Four triangular sides around the base
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glBegin(GL_TRIANGLES); glVertex3fv(B1); glVertex3fv(B2); glVertex3fv(A); glEnd();

    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    glBegin(GL_TRIANGLES); glVertex3fv(B2); glVertex3fv(B3); glVertex3fv(A); glEnd();

    glColor3f(1.0f, 0.5f, 0.0f); // Orange
    glBegin(GL_TRIANGLES); glVertex3fv(B3); glVertex3fv(B4); glVertex3fv(A); glEnd();

    glColor3f(0.6f, 0.2f, 1.0f); // Purple
    glBegin(GL_TRIANGLES); glVertex3fv(B4); glVertex3fv(B1); glVertex3fv(A); glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // depth + double buffer
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cube + Right-Side Pyramid (IT23226746)");

    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(drawScene);
    glutMainLoop();
    return 0;
}