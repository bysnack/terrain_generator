#include <stdlib.h>
#include <GL/glut.h>

#include "TerrainGenerator.hpp"

TerrainGenerator generator;

void display() {
    generator.render();
}

void keyPressed(unsigned char key, int x, int y) {
    generator.onKeyPressed(key);
}

int main(int argc, char** argv) {
    // initialize glut
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Glut");
    glutKeyboardFunc(keyPressed);
    glutDisplayFunc(display);
    glutMainLoop();

    glutCreateWindow("Test");

    return 0;
}