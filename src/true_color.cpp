#include "init.hpp"

namespace untex {
void render_true_color(vec2 *position, u16vec2 *scale, u8vec4 *color, int count) {
  gl_bind_vertex_array(vaos[VAO]);

  gl_use_program(true_color_program);
  gl_draw_arrays_instanced(GL_TRIANGLE_FAN, 0, 4, 1);
}
} // namespace untex
