#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <cmath>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

class Window
{
private:
  GLFWwindow *glfwWindow;
  std::string title;
  unsigned int width;
  unsigned int height;
  bool VSync;

public:
  Window() = default;

  Window(
      const std::string &title,
      unsigned int width,
      unsigned int height,
      bool VSync);

  unsigned int GetWidth();

  unsigned int GetHeight();

  GLFWwindow *GetGlfwWindow();

  void Init(const int versionMajor, const int versionMinor);
};

#endif