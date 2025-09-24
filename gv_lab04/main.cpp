#include <GL/glut.h>

// Function to draw the cube
void createCube() {
    glClear(GL_COLOR_BUFFER_BIT);



    // ----- Back face (Green) -----
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.2,  0.0, -0.4);
        glVertex3f(-0.2,  0.4, -0.4);
        glVertex3f( 0.2,  0.4, -0.4);
        glVertex3f( 0.2,  0.0, -0.4);
    glEnd();

    // ----- Left face (Blue) -----
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.4, -0.2,  0.0);
        glVertex3f(-0.4,  0.2,  0.0);
        glVertex3f(-0.2,  0.4, -0.4);
        glVertex3f(-0.2,  0.0, -0.4);
    glEnd();

    // ----- Right face (Blue) -----
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, -0.2,  0.0);
        glVertex3f(0.0,  0.2,  0.0);
        glVertex3f(0.2,  0.4, -0.4);
        glVertex3f(0.2,  0.0, -0.4);
    glEnd();

    // ----- Top face (White) -----
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.4, 0.2,  0.0);
        glVertex3f( 0.0, 0.2,  0.0);
        glVertex3f( 0.2, 0.4, -0.4);
        glVertex3f(-0.2, 0.4, -0.4);
    glEnd();

    // ----- Bottom face (Yellow) -----
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.4, -0.2,  0.0);
        glVertex3f( 0.0, -0.2,  0.0);
        glVertex3f( 0.2,  0.0, -0.4);
        glVertex3f(-0.2,  0.0, -0.4);
    glEnd();

     // ----- Front face (Red) -----
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.4, -0.2,  0.0);
        glVertex3f(-0.4,  0.2,  0.0);
        glVertex3f( 0.0,  0.2,  0.0);
        glVertex3f( 0.0, -0.2,  0.0);
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Window size & position
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 200);

    // Window title with your IT index
    glutCreateWindow("Cube of IT2025001");

    // Set background color (black)
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Register display function
    glutDisplayFunc(createCube);

    // Start main loop
    glutMainLoop();
    return 0;
}
