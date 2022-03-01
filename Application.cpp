#include "Application.hpp"

Application::Application(
    const std::string &title,
    unsigned int width,
    unsigned int height,
    bool VSync,
    float gammaValue)
{
  window = Window(title, width, height, VSync);
  SetBackgroundColor(Colors::Black);
  Application::gammaValue = gammaValue;
}

unsigned int Application::GetWindowWidth()
{
  return window.GetWidth();
}

unsigned int Application::GetWindowHeight()
{
  return window.GetHeight();
}

GLFWwindow *Application::GetGlfwWindow()
{
  return window.GetGlfwWindow();
}

void Application::SetBackgroundColor(Color backgroundColor)
{
  Application::backgroundColor = backgroundColor;
}

void Application::Init(const int versionMajor, const int versionMinor)
{
  window.Init(versionMajor, versionMinor);
}

void Application::Run()
{
  Init();

  GLFWwindow *glfwWindow{GetGlfwWindow()};

  Setup();

  while (!glfwWindowShouldClose(glfwWindow))
  {
    glClearColor(
        pow(backgroundColor.r / 255.0f, gammaValue),
        pow(backgroundColor.g / 255.0f, gammaValue),
        pow(backgroundColor.b / 255.0f, gammaValue),
        backgroundColor.a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    Draw();

    glfwSwapBuffers(glfwWindow);
    glfwPollEvents();
  }

  Cleanup();

  glfwDestroyWindow(glfwWindow);
  glfwTerminate();
}
