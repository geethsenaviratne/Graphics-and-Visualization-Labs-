// Lab 05 – Geometric Transformations (2D) with GLUT
// Build (Linux):   gcc lab05.c -lGL -lGLU -lglut -lm -o lab05
// Build (Windows/MinGW + freeglut):  gcc lab05.c -lfreeglut -lopengl32 -lglu32 -lm -o lab05

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// ------- Helpers -------
static void drawTriangle(void) {
    glColor3f(1.0f, 0.0f, 0.0f);            // red
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);           // bottom-left
        glVertex2f( 0.5f, -0.5f);           // bottom-right
        glVertex2f( 0.0f,  0.5f);           // top
    glEnd();
}

static void drawAxes(void) {
    glLineWidth(1.0f);
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINES);
        glVertex2f(-1.0f, 0.0f); glVertex2f(1.0f, 0.0f);    // X
        glVertex2f(0.0f, -1.0f); glVertex2f(0.0f, 1.0f);    // Y
    glEnd();
}

// ------- Transform demos -------
void Translate() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    // Original
    drawTriangle();

    // Translated copy
    glPushMatrix();
        glTranslatef(0.5f, 0.3f, 0.0f);
        glColor3f(0.0f, 0.8f, 1.0f);  // cyan to distinguish
        drawTriangle();
    glPopMatrix();

    glutSwapBuffers();
}

void ScaleAboutOrigin() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    // Original
    drawTriangle();

    // Scaled (origin is the pivot)
    glPushMatrix();
        glScalef(2.0f, 1.5f, 1.0f);
        glColor3f(0.2f, 1.0f, 0.2f);
        drawTriangle();
    glPopMatrix();

    glFlush();
}

void ScaleAboutFixedPoint() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    // Fixed point
    const float fx = 0.25f, fy = 0.25f;

    // Original
    drawTriangle();

    // Move pivot to origin -> scale -> move back
    glPushMatrix();
        glTranslatef(fx, fy, 0.0f);
        glScalef(1.8f, 0.7f, 1.0f);
        glTranslatef(-fx, -fy, 0.0f);
        glColor3f(1.0f, 0.6f, 0.0f);
        drawTriangle();
    glPopMatrix();

    glFlush();
}

void RotationAboutOrigin() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    // Original
    drawTriangle();

    // Rotated 45° about origin
    glPushMatrix();
        glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
        glColor3f(0.6f, 0.0f, 1.0f);
        drawTriangle();
    glPopMatrix();

    glFlush();
}

void RotationAboutFixedPoint() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    // Fixed point (the triangle’s lower-left vertex roughly around -0.5,-0.5)
    const float fx = -0.5f, fy = -0.5f;

    // Original
    drawTriangle();

    // Move pivot to origin -> rotate -> move back
    glPushMatrix();
        glTranslatef(fx, fy, 0.0f);
        glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(-fx, -fy, 0.0f);
        glColor3f(0.0f, 0.9f, 0.5f);
        drawTriangle();
    glPopMatrix();

    glFlush();
}

// ------- Composite: Sun–Earth–Moon -------
static float earthOrbitAngle = 0.0f;
static float earthRotationAngle = 0.0f;
static float moonOrbitAngle  = 0.0f;

static void drawCircle(float cx, float cy, float r, int segs, float rcol, float gcol, float bcol) {
    glColor3f(rcol, gcol, bcol);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy); // center
        for (int i = 0; i <= segs; ++i) {
            float t = 2.0f * 3.14159265f * (float)i / (float)segs;
            glVertex2f(cx + r * cosf(t), cy + r * sinf(t));
        }
    glEnd();
}

static void drawGrid() {
    glColor3f(0.35f, 0.35f, 0.35f);
    glBegin(GL_LINES);
        for (float x = -2.0f; x <= 2.01f; x += 0.5f) { glVertex2f(x, -2.0f); glVertex2f(x, 2.0f); }
        for (float y = -2.0f; y <= 2.01f; y += 0.5f) { glVertex2f(-2.0f, y); glVertex2f(2.0f, y); }
    glEnd();
    // axes a bit brighter
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_LINES);
        glVertex2f(-2.0f, 0.0f); glVertex2f(2.0f, 0.0f);
        glVertex2f(0.0f, -2.0f); glVertex2f(0.0f, 2.0f);
    glEnd();
}

void SolarSystemDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();

    // Sun (scaled at origin)
    glPushMatrix();
        glScalef(1.5f, 1.5f, 1.0f);
        drawCircle(0.0f, 0.0f, 0.2f, 50, 1.0f, 0.9f, 0.0f); // yellow
    glPopMatrix();

    // Earth: orbit around Sun, then self-rotate
    glPushMatrix();                                      // world
        glRotatef(earthOrbitAngle, 0, 0, 1);             // orbit around Sun
        glTranslatef(0.8f, 0.0f, 0.0f);                  // orbital radius
        glPushMatrix();                                  // earth local
            glRotatef(earthRotationAngle, 0, 0, 1);      // self rotation
            drawCircle(0.0f, 0.0f, 0.10f, 36, 0.0f, 0.5f, 1.0f); // blue
        glPopMatrix();

        // Moon: nested relative to Earth
        glPushMatrix();                                  // moon local (relative to Earth)
            glRotatef(moonOrbitAngle, 0, 0, 1);
            glTranslatef(0.2f, 0.0f, 0.0f);
            drawCircle(0.0f, 0.0f, 0.04f, 24, 0.95f, 0.95f, 0.95f);
        glPopMatrix();
    glPopMatrix();

    // (Optional) Earth orbit path
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 100; ++i) {
            float t = 2.0f * 3.14159265f * i / 100.0f;
            glVertex2f(0.8f * cosf(t), 0.8f * sinf(t));
        }
    glEnd();

    glutSwapBuffers();
}

void timer(int v) {
    earthOrbitAngle     += 0.2f;   // slow
    earthRotationAngle  += 1.0f;   // faster
    moonOrbitAngle      += 0.5f;   // medium
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);   // ~60 FPS
}

void init(void) {
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void printInstructions(void) {
    printf("Transforms: Translate / Scale / Rotate; Composite: Sun-Earth-Moon\n");
    printf("In main(), switch which glutDisplayFunc to run.\n");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 700);
    glutCreateWindow("IT23226128 - Lab 05 - Geometric Transformations");

    init();
    printInstructions();

    // === Pick what to show: uncomment ONE ===
    //glutDisplayFunc(Translate);
    //glutDisplayFunc(ScaleAboutOrigin);
    //glutDisplayFunc(ScaleAboutFixedPoint);
    //glutDisplayFunc(RotationAboutOrigin);
    //glutDisplayFunc(RotationAboutFixedPoint);
    glutDisplayFunc(SolarSystemDisplay);  // composite demo

    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
