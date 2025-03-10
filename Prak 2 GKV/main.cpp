#include <GL/glut.h>
#include <cmath>

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawSun() {
    glColor3f(1.0, 1.0, 0.0);
    drawCircle(-0.8, 0.6, 0.15, 30);
}

void drawCloud(float cx, float cy) {
    glColor3f(0.9, 0.9, 0.9);
    drawCircle(cx, cy, 0.1, 20);
    drawCircle(cx + 0.1, cy + 0.05, 0.12, 20);
    drawCircle(cx + 0.2, cy, 0.1, 20);
}

void drawRollsRoyce() {
    glPushMatrix();
    
    // Badan mobil (lebih kotak khas Rolls-Royce)
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6, -0.2);
    glVertex2f(0.6, -0.2);
    glVertex2f(0.6, 0.15);
    glVertex2f(-0.6, 0.15);
    glEnd();

    // Atap mobil
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, 0.15);
    glVertex2f(0.4, 0.15);
    glVertex2f(0.35, 0.3);
    glVertex2f(-0.35, 0.3);
    glEnd();

    // Pintu
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2, -0.2);
    glVertex2f(0.1, -0.2);
    glVertex2f(0.1, 0.15);
    glVertex2f(-0.2, 0.15);
    glEnd();

    // Kaca mobil
    glColor3f(0.7, 0.9, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.35, 0.15);
    glVertex2f(-0.05, 0.15);
    glVertex2f(-0.05, 0.28);
    glVertex2f(-0.3, 0.28);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2f(0.05, 0.15);
    glVertex2f(0.35, 0.15);
    glVertex2f(0.3, 0.28);
    glVertex2f(0.05, 0.28);
    glEnd();

    // Grill depan Rolls-Royce
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(0.55, -0.2);
    glVertex2f(0.6, -0.2);
    glVertex2f(0.6, 0.15);
    glVertex2f(0.55, 0.15);
    glEnd();

    // Roda kanan
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(0.35, -0.25, 0.12, 20);

    // Roda kiri
    drawCircle(-0.35, -0.25, 0.12, 20);
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    // Menggambar langit
    glColor3f(0.5, 0.8, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glVertex2f(1, 0.3);
    glVertex2f(-1, 0.3);
    glEnd();
    
    // Menggambar jalan raya
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 0.3);
    glVertex2f(1, 0.3);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();
    
    // Garis jalan
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(3);
    glBegin(GL_LINES);
    for (float i = -0.9; i < 1.0; i += 0.4) {
        glVertex2f(i, -0.35);
        glVertex2f(i + 0.2, -0.35);
    }
    glEnd();
    
    // Menggambar matahari
    drawSun();
    
    // Menggambar awan
    drawCloud(-0.5, 0.7);
    drawCloud(0.2, 0.8);
    drawCloud(0.6, 0.75);
    
    // Menggambar mobil Rolls-Royce
    glTranslatef(0.0, -0.2, 0.0);
    drawRollsRoyce();

    glutSwapBuffers();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Rolls-Royce di Jalan Raya");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

