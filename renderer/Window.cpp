#include <stdexcept>

#include "Window.hpp"

Window::Window(
    const std::string &title,
    unsigned int width,
    unsigned int height,
    bool VSync)
{
  Window::title = title;
  Window::width = width;
  Window::height = height;
  Window::VSync = VSync;
}

unsigned int Window::GetWidth()
{
  return width;
}

unsigned int Window::GetHeight()
{
  return height;
}

GLFWwindow *Window::GetGlfwWindow()
{
  return glfwWindow;
}

void Window::Init(
    const int versionMajor,
    const int versionMinor,
    const unsigned int samples)
{
  if (!glfwInit())
    std::runtime_error("Could not initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
  glfwWindowHint(GLFW_SAMPLES, samples);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  Window::glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!glfwWindow)
    std::runtime_error("Failed to create GLFW window");

  glfwMakeContextCurrent(glfwWindow);

  gladLoadGL();

  glViewport(0, 0, width, height);

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_MULTISAMPLE);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  glFrontFace(GL_CCW);

  if (!VSync)
    glfwSwapInterval(0);
}
