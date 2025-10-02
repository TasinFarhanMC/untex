#pragma once
#include <glext/gl.h>
#include <untex/untex.hpp>

constexpr int VBO_SIZE = 4;
extern GLuint vbos[VBO_SIZE];
constexpr int BASE_POS = 0;
constexpr int POS = 1;
constexpr int SCALE = 2;
constexpr int COLOR = 3;

inline GLuint &base_pos_vbo = vbos[BASE_POS];
inline GLuint &pos_vbo = vbos[POS];
inline GLuint &scale_vbo = vbos[SCALE];
inline GLuint &color_vbo = vbos[COLOR];

constexpr int VAO_SIZE = 1;
extern GLuint vaos[VAO_SIZE];
inline GLuint &true_color_vao = vaos[0];

extern GLuint true_color_program;
