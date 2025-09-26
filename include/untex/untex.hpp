#pragma once
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_uint2_sized.hpp>
#include <glm/ext/vector_uint4_sized.hpp>
#include <optional>
#include <string>

using namespace glm;

namespace untex {

std::optional<std::string> init(uint render_ubo);
void clean();

void render_true_color(vec2 *position, u16vec2 *scale, u8vec4 *color, int count);
} // namespace untex
