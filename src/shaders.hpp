#pragma once

static const char *true_color_vert = R"(
#version 330 core

layout(location = 0) in vec2 base_pos;
layout(location = 1) in vec2 pos;
layout(location = 2) in uvec2 scale;
layout(location = 3) in vec4 color;

const vec2 DIM = vec2(160.0f, 90.0f);
flat out vec4 fColor;

void main() {
  vec2 world_pos = base_pos * scale + pos;
  gl_Position = vec4(world_pos * 2 / DIM - 1, 0.0f, 1.0f);
  fColor = color;
}
)";

static const char *true_color_frag = R"(
#version 330 core

flat in vec4 fColor;
out vec4 color;

void main() {
  color = fColor;
}
)";
