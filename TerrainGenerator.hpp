#include <GL/glut.h>
#include <ctime>

#include "PerlinNoise/PerlinNoise.hpp"

class TerrainGenerator {
public:
    void render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glMatrixMode(GL_PROJECTION);
        gluPerspective(60, 1.f, .1, 50);
        glTranslatef(0.f, 0.f, -2.f);
        glRotatef(120.f, 1.f, 0.f, 0.f);

        float yoff = _position + 0.f;
        for (int i = 0; i < _rows - 1; ++i) {
            float xoff = 0.f;
            glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j < _columns; ++j) {
                glVertex3f(
                    (j - _rows / 2.f) / _scale,
                    (i - _columns / 2.f) / _scale,
                    _perlin.accumulatedOctaveNoise2D_0_1(
                        yoff / _frequency.first,
                        xoff / _frequency.second,
                        8
                    )
                );
            
                glVertex3f(
                    (j - _rows / 2.f) / _scale,
                    (i - _columns / 2.f + 1) / _scale,
                    _perlin.accumulatedOctaveNoise2D_0_1(
                        (yoff + 0.01f) / _frequency.first,
                        xoff / _frequency.second,
                        8
                    )
                );
                xoff += 0.01f;
            }
            glEnd();
            yoff += 0.01;
        }
        glutSwapBuffers();
    }

    void onKeyPressed(unsigned char key) {
        switch (key) {
            case 'w':
                _position -= 0.01f;
                break;
            case 's':
                _position += 0.01f;
                break;
        }
        glutPostRedisplay();
    }

private:
    static constexpr std::size_t                _scale{ 20 };
    static constexpr std::size_t                _width{ 2000 };
    static constexpr std::size_t                _height{ 2000 };
    static constexpr std::pair<float, float>    _frequency{ _width / 10000.f, _height / 10000.f };
    static constexpr std::uint32_t              _rows{ _height / _scale };
    static constexpr std::uint32_t              _columns{ _width / _scale };
    const siv::PerlinNoise                      _perlin{ static_cast<std::uint32_t>(std::time(nullptr)) };
    float                                       _position{ 0.f };
};