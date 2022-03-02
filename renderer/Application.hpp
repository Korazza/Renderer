#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Window.hpp"
#include "Color.hpp"

class Application
{
private:
  Window window;
  Color backgroundColor;
  float gammaValue;

public:
  Application(
      const std::string &title = "App",
      unsigned int width = 900,
      unsigned int height = 900,
      bool VSync = true,
      float gammaValue = 2.2f);

  unsigned int GetWindowWidth();

  unsigned int GetWindowHeight();

  GLFWwindow *GetGlfwWindow();

  void SetBackgroundColor(Color backgroundColor);

  void Init(const int versionMajor = 3, const int versionMinor = 3);

  void Run();

  virtual void Setup() = 0;

  virtual void Draw() = 0;

  virtual void Cleanup() = 0;
};

#endif