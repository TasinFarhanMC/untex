#include "global.hpp"

namespace untex {
void upload_true_color(vec2 *position, u16vec2 *scale, u8vec4 *color, int count) {
  gl_bind_buffer(GL_ARRAY_BUFFER, pos_vbo);
  gl_buffer_data(GL_ARRAY_BUFFER, sizeof(vec2) * count, position, GL_DYNAMIC_DRAW);

  gl_bind_buffer(GL_ARRAY_BUFFER, scale_vbo);
  gl_buffer_data(GL_ARRAY_BUFFER, sizeof(u16vec2) * count, scale, GL_DYNAMIC_DRAW);

  gl_bind_buffer(GL_ARRAY_BUFFER, color_vbo);
  gl_buffer_data(GL_ARRAY_BUFFER, sizeof(u8vec4) * count, color, GL_DYNAMIC_DRAW);

  gl_bind_vertex_array(true_color_vao);
}

void render_buffered_true_color(int start, int count) {
  gl_use_program(true_color_program);
  gl_draw_arrays_instanced_base_instance(GL_TRIANGLE_FAN, 0, 4, count, start);
}
} // namespace untex
