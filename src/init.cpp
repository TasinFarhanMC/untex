#include "global.hpp"
#include "shaders.hpp"

GLuint vbos[VBO_SIZE];
GLuint vaos[VAO_SIZE];

GLuint true_color_program;

void compile_shader(GLuint shader, const char *source) {
  gl_shader_source(shader, 1, &source, nullptr);

  // Compile the shader
  gl_compile_shader(shader);

  // Check compilation status
  GLint success = 0;
  gl_get_shaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) { // Get the length of the info log GLint log_length = 0;
    int log_length;
    gl_get_shaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

    // Allocate buffer for the log
    char *info_log = new char[log_length];
    gl_get_shader_info_log(shader, log_length, nullptr, info_log);

    // Print error and exit or handle
    fprintf(stderr, "Shader compilation failed:\n%s\n", info_log);
    delete[] info_log;
  }
}

GLuint vertex;
GLuint fragment;

GLuint create_program(const char *vertex_src, const char *fragment_src) {
  GLuint program = gl_create_program();
  // Create shader objects
  vertex = gl_create_shader(GL_VERTEX_SHADER);
  fragment = gl_create_shader(GL_FRAGMENT_SHADER);

  // Compile shaders
  compile_shader(vertex, vertex_src);
  compile_shader(fragment, fragment_src);

  // Attach shaders to program
  gl_attach_shader(program, vertex);
  gl_attach_shader(program, fragment);

  // Link program
  gl_link_program(program);

  // Check link status
  GLint success = 0;
  gl_get_programiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    GLint log_length = 0;
    gl_get_programiv(program, GL_INFO_LOG_LENGTH, &log_length);

    char *info_log = new char[log_length];
    gl_get_program_info_log(program, log_length, nullptr, info_log);

    fprintf(stderr, "Program linking failed:\n%s\n", info_log);
    delete[] info_log;
  }

  return program;
}

namespace untex {
std::string init() {
  if (gl_gen_buffers == nullptr) { return "GLAD Not Loaded"; }

  gl_gen_vertex_arrays(VAO_SIZE, vaos);
  gl_gen_buffers(VBO_SIZE, vbos);

  constexpr vec2 base_pos[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

  gl_bind_buffer(GL_ARRAY_BUFFER, base_pos_vbo);
  gl_buffer_data(GL_ARRAY_BUFFER, sizeof(base_pos), base_pos, GL_STATIC_DRAW);

  vertex = gl_create_shader(GL_VERTEX_SHADER);
  fragment = gl_create_shader(GL_FRAGMENT_SHADER);

  true_color_program = create_program(true_color_vert, true_color_frag);

  gl_bind_vertex_array(true_color_vao);

  gl_bind_vertex_buffer(BASE_POS, base_pos_vbo, 0, sizeof(vec2));
  gl_enable_vertex_attrib_array(0);
  gl_vertex_attrib_format(0, 2, GL_FLOAT, GL_FALSE, 0);
  gl_vertex_attrib_binding(0, BASE_POS);

  gl_bind_vertex_buffer(POS, pos_vbo, 0, sizeof(vec2));
  gl_enable_vertex_attrib_array(1);
  gl_vertex_attrib_format(1, 2, GL_FLOAT, GL_FALSE, 0);
  gl_vertex_attrib_divisor(1, 1);
  gl_vertex_attrib_binding(1, POS);

  gl_delete_shader(vertex);
  gl_delete_shader(fragment);
  return "";
}

void clean() {
  gl_delete_buffers(VBO_SIZE, vbos);
  gl_delete_vertex_arrays(VAO_SIZE, vaos);
  gl_delete_program(true_color_program);
}
} // namespace untex
