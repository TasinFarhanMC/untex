#include "init.hpp"

namespace untex {
void render_true_color(vec2 *position, u16vec2 *scale, u8vec4 *color, int count) {
  gl_bind_buffer(GL_ARRAY_BUFFER, vbos[POS]);
  gl_buffer_data(GL_ARRAY_BUFFER, sizeof(vec2) * count, position, GL_DYNAMIC_DRAW);

  gl_bind_buffer(GL_ARRAY_BUFFER, vbos[SCALE]);
  gl_buffer_data(GL_ARRAY_BUFFER, sizeof(u16vec2) * count, scale, GL_DYNAMIC_DRAW);

  // gl_bind_buffer(GL_ARRAY_BUFFER, vbos[COLOR]);
  // gl_buffer_data(GL_ARRAY_BUFFER, sizeof(u8vec4) * count, color, GL_DYNAMIC_DRAW);

  gl_bind_vertex_array(vaos[VAO]);

  gl_use_program(true_color_program);
  gl_draw_arrays_instanced(GL_TRIANGLE_FAN, 0, 4, count);
  gl_draw_arrays(GL_TRIANGLE_FAN, 0, 4);
}
} // namespace untex
