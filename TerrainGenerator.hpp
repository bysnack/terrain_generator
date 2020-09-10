#include <GL/glut.h>
#include <ctime>
#include <functional>
#include <cstdint>
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include "PerlinNoise/PerlinNoise.hpp"

class TerrainGenerator {
public:
    using resolution_t = std::pair<uint16_t, uint16_t>;

    /**
     *  Non constructible static class
     */
    TerrainGenerator() = delete;
    TerrainGenerator(const TerrainGenerator&) = delete;
    TerrainGenerator(TerrainGenerator&&) = delete;

    /**
     *  Initializes the terrain generator
     *
     *  @param  argc    The count of command line arguments provided to the application
     *  @param  argv    A pointer to the subsequent command line argument values
     */
    static void init(int argc, char** argv) {
        // parse arguments
        auto [resolution] = TerrainGenerator::parseCommandLine(argc, argv);

        // initialize glut
        glutInit(&argc, argv);
        glutInitWindowSize(resolution.first, resolution.second);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutCreateWindow("Terrain Generator");
        glutKeyboardFunc(&TerrainGenerator::onKeyPressed);
        glutDisplayFunc(&TerrainGenerator::render);

        // start main loop
        glutMainLoop();
    }

private:
    static std::tuple<resolution_t> parseCommandLine(int argc, char** argv) {
        // return value with default values
        std::tuple<resolution_t> retval{ {800, 600} };

        // define a vector of string views to the values
        std::vector<std::string_view> args{ argv, argv + argc };

        // iterate over the views
        for (auto it = args.begin(); it != args.end(); ++it) {
            if (*it == "-h" || *it == "--help") {
                std::cout << "Perlin Noise Terrain Generator" << std::endl
                    << "Usage: ./terrain [OPTION]..." << std::endl
                    << "Optional arguments:" << std::endl
                    << "    -r, --resolution [width height]" << std::endl;
            } else if (*it == "-r" || *it == "--resolution") {
                std::get<resolution_t>(retval) = { std::stoi(std::string{ *(++it) }), std::stoi(std::string{ *(++it) }) };
            }
        }

        return retval;
    }

    static void render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glMatrixMode(GL_PROJECTION);
        gluPerspective(60, 1.f, .1, 50);
        glTranslatef(0.f, 0.f, -1.f);
        glRotatef(120.f, 1.f, 0.f, 0.f);

        // define a y offset position
        float yoff = _position;
        for (int i = 0; i < _rows; ++i) {
            float xoff = 0.f;

            // each row defines a line strip
            glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j <= _columns; ++j) {
                // we need to create two vertext, one on top of the other
                // make the first one start at [j, i], scale it down so we can fit one of
                // the resultant triangles per column and translate it to the origin
                glVertex3f(
                    (j / (_columns / 2.f)) - 1.f,
                    (i / (_rows / 2.f)) - 1.f,
                    _perlin.accumulatedOctaveNoise2D_0_1(
                        yoff / _frequency.first,
                        xoff / _frequency.second,
                        8
                    )
                );

                // the second one has to be "on top", we accomplish this by creating the same
                // vertex increasing its Y component by 1
                glVertex3f(
                    (j / (_columns / 2.f)) - 1.f,
                    ((1.f + i) / (_rows / 2.f)) - 1.f,
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

    static void onKeyPressed(unsigned char key, int x, int y) {
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
    static constexpr std::size_t                _scale{ 30 };
    static constexpr std::size_t                _width{ 1920 };
    static constexpr std::size_t                _height{ 1080 };
    static constexpr std::pair<float, float>    _frequency{ _width / 10000.f, _height / 10000.f };
    static constexpr std::uint32_t              _rows{ _height / _scale };
    static constexpr std::uint32_t              _columns{ _width / _scale };
    inline static float                         _position{ 0.f };
    inline static const siv::PerlinNoise        _perlin{ static_cast<std::uint32_t>(std::time(nullptr)) };
};
