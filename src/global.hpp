#pragma once
#include <glext/gl.h>
#include <untex/untex.hpp>

constexpr int VBO_SIZE = 2;
extern GLuint vbos[VBO_SIZE];
constexpr int BASE_POS = 0;
constexpr int POS = 1;
inline GLuint &base_pos_vbo = vbos[BASE_POS];
inline GLuint &pos_vbo = vbos[POS];

constexpr int VAO_SIZE = 1;
extern GLuint vaos[VAO_SIZE];
inline GLuint &true_color_vao = vaos[0];

extern GLuint true_color_program;
