#include "global.hpp"

namespace untex {
void render_true_color(vec2 *position, int count) {
  gl_bind_buffer(GL_ARRAY_BUFFER, pos_vbo);
  gl_buffer_data(GL_ARRAY_BUFFER, sizeof(vec2) * count, position, GL_DYNAMIC_DRAW);
  gl_bind_vertex_array(true_color_vao);

  gl_use_program(true_color_program);
  gl_draw_arrays_instanced(GL_TRIANGLE_FAN, 0, 4, count);
}
} // namespace untex
