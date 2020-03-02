#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "PerlinNoise/PerlinNoise.hpp"
#include <ctime>
#include <vector>

constexpr int height = 800;
constexpr int width = 1600;
const float scale = 20;

float angle = 60.f;
float x = -1.f;
float y = 0.f;
float z = -0.f;
const siv::PerlinNoise perlin(std::time(nullptr));
float flying = 0.f;

void render(void) {
    const int rows = height / scale;
    const int columns = width / scale;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, 1.f, .1, 50);

    glTranslatef(0.0f, -0.2f, -2.f);
    glRotatef(120.f, 1.f, 0.f, 0.f);

    const float fx = width / 10000.f;
    const float fy = height / 10000.f;

    std::vector<std::vector<float>> terrains;
    terrains.reserve(rows);

    float yoff = flying + 0.f;
    for (int i = -(rows / 2); i < rows / 2; ++i) {
        terrains.push_back({});
        terrains.back().reserve(columns);
        float xoff = 0.f;
        for (int j = -(columns) / 2; j < columns / 2; ++j) {
            terrains.back().push_back(perlin.accumulatedOctaveNoise2D_0_1(yoff/fy, xoff/fx, 8));
            xoff += 0.01f;
        }
        yoff += 0.01;
    }

    for (int i = -(rows / 2); i < static_cast<int>(rows / 2) - 1; ++i) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = -(columns) / 2; j < columns / 2; ++j) {
                glVertex3f(j / scale, i / scale, terrains[i + (rows) / 2][j + (columns) / 2] );
                glVertex3f(j / scale, (i + 1) / scale, terrains[i + 1 + (rows) / 2][j + (columns) / 2] );
        }
        glEnd();
    }
    glutSwapBuffers();
}

void key(unsigned char k, int x, int y) {
    switch (k) {
        case 'w':
            flying -= 0.01f;
            glutPostRedisplay();
            break;
    }
 }

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(-1 ,-1);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Glut");
    glutKeyboardFunc(key);
    glutDisplayFunc(render);
    glutMainLoop();

    glutCreateWindow("Test");

    return 0;
}