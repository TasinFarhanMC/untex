#pragma once
#include <glext/gl.h>
#include <untex/untex.hpp>

extern GLuint vbos[4];
constexpr int POS = 0;
constexpr int SCALE = 1;
constexpr int COLOR = 2;
constexpr int BASE_POS = 3;

extern GLuint vaos[1];
constexpr int VAO = 0;

extern GLuint true_color_program;
