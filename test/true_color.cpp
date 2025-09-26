#include <glext/gl.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_uint2_sized.hpp>
#include <glm/ext/vector_uint4_sized.hpp>
#include <iostream>
#include <untex/untex.hpp>

#include <GLFW/glfw3.h>

int main() {
  // GLFW + OpenGL 3.3 core
  if (!glfwInit()) return -1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *window = glfwCreateWindow(800, 600, "Untex Test", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!glext_load_gl(glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD\n";
    return -1;
  }

  // Create UBO for render dimensions
  GLuint render_ubo;
  gl_gen_buffers(1, &render_ubo);
  gl_bind_buffer(GL_UNIFORM_BUFFER, render_ubo);
  glm::vec2 dim(800.0f, 600.0f);
  gl_buffer_data(GL_UNIFORM_BUFFER, sizeof(glm::vec2), &dim, GL_STATIC_DRAW);

  // Initialize untex with UBO
  if (untex::init(render_ubo) != untex::Error::None) {
    std::cerr << "Failed to initialize untex\n";
    return -1;
  }

  // Example quads
  glm::vec2 positions[] = {{100, 100}, {300, 200}, {500, 400}};
  glm::u16vec2 scales[] = {{50, 50}, {80, 40}, {60, 90}};
  glm::u8vec4 colors[] = {{255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}};
  const int count = 3;

  while (!glfwWindowShouldClose(window)) {
    GLenum err;
    while ((err = gl_get_error()) != GL_NO_ERROR) { std::cerr << "OpenGL error: " << err << "\n"; }

    gl_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
    gl_clear(GL_COLOR_BUFFER_BIT);

    // Render instanced quads
    untex::render_true_color(positions, scales, colors, count);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  untex::clean();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
