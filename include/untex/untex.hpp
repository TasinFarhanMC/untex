#pragma once
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_uint2_sized.hpp>
#include <glm/ext/vector_uint4_sized.hpp>
#include <string>

using namespace glm;

namespace untex {

std::string init();
void clean();

void upload_true_color(vec2 *position, u16vec2 *scale, u8vec4 *color, int count);
void render_buffered_true_color(int start, int count);
inline void render_true_color(vec2 *position, u16vec2 *scale, u8vec4 *color, int count) {
  upload_true_color(position, scale, color, count);
  render_buffered_true_color(0, count);
}
} // namespace untex
