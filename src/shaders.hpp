#pragma once

static const char *true_color_vert = R"(
#version 330 core

layout(location = 0) in vec2 base_pos;
layout(location = 1) in vec2 pos;

void main() {
  gl_Position = vec4(base_pos + pos, 0.0, 1.0);
}
)";

static const char *true_color_frag = R"(
#version 330 core

out vec4 color;

void main() {
  color = vec4(1.0);
}
)";
