#pragma once

static const char *true_color_vert = R"(
#version 330 core
#extension GL_ARB_shading_language_420pack: require

layout(location = 0) in vec2 base_pos;
layout(location = 1) in vec2 pos;
layout(location = 2) in uvec2 scale;
layout(location = 3) in uint color;

layout(std140, binding = 0) uniform Render {
  vec2 dim;
} render;

flat out vec4 fColor;

void main() {
  // const vec2 world_pos = base_pos * scale + pos;
  // gl_Position = vec4(world_pos * 2 / render.dim - 1, 0.0f, 1.0f);
  gl_Position = vec4(base_pos, 0.0, 1.0);

  // fColor.r = float((color >> 24) & 0xFFu) / 255.0;
  // fColor.g = float((color >> 16) & 0xFFu) / 255.0;
  // fColor.b = float((color >> 8)  & 0xFFu) / 255.0;
  // fColor.a = float(color & 0xFFu) / 255.0;
}
)";

static const char *true_color_frag = R"(
#version 330 core

flat in vec4 fColor;
out vec4 color;

void main() {
  color = vec4(1.0);
}
)";
