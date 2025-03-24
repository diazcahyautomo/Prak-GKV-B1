#include <GL/glut.h>

// Inisialisasi Pencahayaan (Lighting)
void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    GLfloat lightPos[] = {5.0f, 5.0f, 10.0f, 1.0f};   // Posisi lampu
    GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Warna cahaya putih

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
}

// Fungsi untuk menggambar kubus solid dengan warna neon
void drawSolidCube(float size, float r, float g, float b) {
    GLfloat materialColor[] = {r, g, b, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glutSolidCube(size);
}

// Fungsi untuk menggambar lampu dengan efek cahaya
void drawLightCube(float size, float r, float g, float b) {
    GLfloat emissionColor[] = {r, g, b, 1.0f};
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
    glutSolidCube(size);
    GLfloat noEmission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
    glPopMatrix();
}

// Fungsi untuk menggambar roda dengan velg
void drawWheel(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.0f, 0.0f, 0.0f);  // Warna hitam untuk ban
    glutSolidTorus(0.15, 0.5, 20, 30);

    glColor3f(0.8f, 0.8f, 0.8f);  // Warna abu-abu untuk velg
    glutSolidTorus(0.08, 0.3, 10, 25);
    glPopMatrix();
}

// Fungsi untuk menggambar mobil
void drawCar() {
    glPushMatrix();

    // **Bodi utama (biru metalik)**
    glPushMatrix();
    glScalef(4.0f, 1.2f, 2.0f);
    drawSolidCube(1.0f, 0.0f, 0.0f, 1.8f);  // Biru metalik
    glPopMatrix();

    // **Atap (hitam)**
    glPushMatrix();
    glTranslatef(0.0f, 1.1f, 0.0f);
    glScalef(2.5f, 0.7f, 1.5f);
    drawSolidCube(1.0f, 0.0f, 0.0f, 0.0f);  // Hitam
    glPopMatrix();

    // **Jendela hitam**
    glPushMatrix();
    glTranslatef(0.0f, 1.2f, 0.0f);
    glScalef(2.4f, 0.5f, 1.4f);
    drawSolidCube(1.0f, 0.2f, 0.2f, 0.2f);
    glPopMatrix();

    // **Lampu depan (kuning terang)**
    glPushMatrix();
    glTranslatef(1.8f, 0.0f, 1.01f);
    glScalef(0.3f, 0.3f, 0.1f);
    drawLightCube(1.0f, 1.0f, 1.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8f, 0.0f, 1.01f);
    glScalef(0.3f, 0.3f, 0.1f);
    drawLightCube(1.0f, 1.0f, 1.0f, 0.0f);
    glPopMatrix();

    // **Lampu belakang (merah terang)**
    glPushMatrix();
    glTranslatef(1.8f, 0.0f, -1.01f);
    glScalef(0.3f, 0.3f, 0.1f);
    drawLightCube(1.0f, 1.0f, 0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8f, 0.0f, -1.01f);
    glScalef(0.3f, 0.3f, 0.1f);
    drawLightCube(1.0f, 1.0f, 0.0f, 0.0f);
    glPopMatrix();

    // **Roda**
    drawWheel(-1.6f, -0.6f, 1.2f);
    drawWheel(1.6f, -0.6f, 1.2f);
    drawWheel(-1.6f, -0.6f, -1.2f);
    drawWheel(1.6f, -0.6f, -1.2f);

    glPopMatrix();
}

// Fungsi untuk menampilkan mobil
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(6, 4, 6, 0, 0, 0, 0, 1, 0);

    drawCar();

    glutSwapBuffers();
}

// Fungsi untuk menangani ukuran jendela
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mobil 3D Realistis dengan Lampu");

    initLighting();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
