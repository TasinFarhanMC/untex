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
  //
  if (const std::string error = untex::init(); error.size()) {
    std::cout << error << std::endl;
    return -1;
  }

  // Example quads
  glm::vec2 positions[] = {{.4, .4}, {-1, -1}};
  glm::u16vec2 scales[] = {{.6, .6}, {.5, .5}, {60, 9}};
  glm::u8vec4 colors[] = {{255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}};
  const int count = 2;

  constexpr float SPACE_HEIGHT = 90.0f;
  constexpr float SPACE_WIDTH = 160.0f;

  glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
    float min = std::min(width / SPACE_WIDTH, height / SPACE_HEIGHT);
    float m_width = min * SPACE_WIDTH;
    float m_height = min * SPACE_HEIGHT;
    gl_viewport(std::abs(width - m_width) / 2, std::abs(height - m_height) / 2, m_width, m_height);
  });

  while (!glfwWindowShouldClose(window)) {
    GLenum err;
    while ((err = gl_get_error()) != GL_NO_ERROR) { std::cerr << "OpenGL error: " << err << "\n"; }

    gl_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
    gl_clear(GL_COLOR_BUFFER_BIT);

    // Render instanced quads
    untex::render_true_color(positions, count);

    glfwSwapBuffers(window);
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }

    static bool aspect_ratio_locked = false;
    static bool v_pressed_last_frame = false;
    bool v_pressed = glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS;

    // Detect key press edge (just pressed)
    if (v_pressed && !v_pressed_last_frame) {
      aspect_ratio_locked = !aspect_ratio_locked; // toggle
      if (aspect_ratio_locked) {
        glfwSetWindowAspectRatio(window, SPACE_WIDTH, SPACE_HEIGHT);
      } else {
        glfwSetWindowAspectRatio(window, GLFW_DONT_CARE, GLFW_DONT_CARE);
      }
    }

    v_pressed_last_frame = v_pressed;
  }

  untex::clean();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
