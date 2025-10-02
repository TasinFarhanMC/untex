#pragma once
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_uint2_sized.hpp>
#include <glm/ext/vector_uint4_sized.hpp>
#include <string>

using namespace glm;

namespace untex {

std::string init();
void clean();

void render_true_color(vec2 *position, int count);
} // namespace untex
