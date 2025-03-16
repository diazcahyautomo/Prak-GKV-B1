#include <windows.h>
#include <GL/glut.h>
#include <cmath>

// Variabel untuk rotasi lengan & jari
float rotasiLenganX = 0.0, rotasiLenganY = 0.0;
float rotasiPergelangan = 0.0;
float rotasiJari[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
bool animasiOtomatis = false;

// Inisialisasi pencahayaan dan material
void setupLighting() {
    GLfloat ambientLight[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat diffuseLight[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat specularLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightPosition[] = {2.0, 5.0, 5.0, 1.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
}

// Fungsi menggambar silinder (lengan, jari)
void drawCylinder(float radius, float height) {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluCylinder(quad, radius, radius, height, 20, 20);
    gluDeleteQuadric(quad);
}

// Fungsi menggambar bola (sendi)
void drawSphere(float radius) {
    glutSolidSphere(radius, 30, 30);
}

// Fungsi menggambar satu jari dengan 2 sendi
void drawFinger(float rotasi) {
    glPushMatrix();
    glRotatef(rotasi, 1, 0, 0);
    drawCylinder(0.08, 0.3);
    glTranslatef(0.0, 0.0, 0.3);
    drawSphere(0.08);
    drawCylinder(0.07, 0.2);
    glPopMatrix();
}

// Fungsi menggambar tangan robot
void drawHand() {
    glPushMatrix();

    // Lengan bawah
    glColor3f(0.7, 0.2, 0.2); // Warna merah metalik
    drawCylinder(0.3, 1.5);
    glTranslatef(0.0, 0.0, 1.5);
    drawSphere(0.3);

    // Pergelangan tangan
    glRotatef(rotasiPergelangan, 0, 1, 0);
    glColor3f(0.8, 0.5, 0.5); // Warna merah muda
    drawCylinder(0.4, 0.3);
    glTranslatef(0.0, 0.0, 0.3);
    drawSphere(0.4);

    // Jari-jari
    glColor3f(0.8, 0.8, 0.8); // Warna abu-abu metalik
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        float offset = (i - 2) * 0.2;
        glTranslatef(offset, 0.2, 0.1);
        drawFinger(rotasiJari[i]);
        glPopMatrix();
    }

    glPopMatrix();
}

// Fungsi tampilan
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Kamera 3D
    gluLookAt(2.0, 2.0, 5.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
    
    // Rotasi lengan
    glPushMatrix();
    glRotatef(rotasiLenganX, 1, 0, 0);
    glRotatef(rotasiLenganY, 0, 1, 0);
    drawHand();
    glPopMatrix();
    
    glutSwapBuffers();
}

// Fungsi keyboard untuk interaksi
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': rotasiLenganX -= 5; break;  // Gerakkan lengan ke atas
        case 's': rotasiLenganX += 5; break;  // Gerakkan lengan ke bawah
        case 'a': rotasiLenganY -= 5; break;  // Putar lengan ke kiri
        case 'd': rotasiLenganY += 5; break;  // Putar lengan ke kanan
        case 'q': rotasiPergelangan -= 5; break; // Putar pergelangan tangan kiri
        case 'e': rotasiPergelangan += 5; break; // Putar pergelangan tangan kanan
        case '1': rotasiJari[0] = (rotasiJari[0] == 0) ? 45 : 0; break;
        case '2': rotasiJari[1] = (rotasiJari[1] == 0) ? 45 : 0; break;
        case '3': rotasiJari[2] = (rotasiJari[2] == 0) ? 45 : 0; break;
        case '4': rotasiJari[3] = (rotasiJari[3] == 0) ? 45 : 0; break;
        case '5': rotasiJari[4] = (rotasiJari[4] == 0) ? 45 : 0; break;
        case 'm': animasiOtomatis = !animasiOtomatis; break;
        case 27: exit(0); // ESC untuk keluar
    }
    glutPostRedisplay();
}

// Fungsi untuk animasi otomatis
void timer(int value) {
    if (animasiOtomatis) {
        rotasiLenganY += 1;
        if (rotasiLenganY > 360) rotasiLenganY = 0;
        for (int i = 0; i < 5; i++) {
            rotasiJari[i] = 15 * sin(glutGet(GLUT_ELAPSED_TIME) / 500.0);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

// Fungsi untuk menangani perubahan ukuran jendela
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tangan Robot Realistis");

    setupLighting();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(30, timer, 0);
    glutMainLoop();
    
    return 0;
}

