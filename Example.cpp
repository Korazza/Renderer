#include <iostream>
#include <math.h>
#include "renderer/include/imgui/imgui.h"
#include "renderer/include/imgui/imgui_impl_glfw.h"
#include "renderer/include/imgui/imgui_impl_opengl3.h"

#include "renderer/Application.hpp"
#include "renderer/Model.hpp"

unsigned int width{900};
unsigned int height{900};
float gammaValue{2.2f};

GLFWwindow *glfwWindow;
ImGuiIO io;

Shader *shaderProgram{nullptr};

glm::vec4 lightColor{glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)};
glm::vec3 lightPos{glm::vec3(0.5f, 0.5f, 0.5f)};

Camera *camera{nullptr};
Model *jupiter{nullptr};

class App : public Application
{
public:
  App()
      : Application("OpenGL Test", width, height)
  {
    SetBackgroundColor(Colors::Black);
  }

  void Setup()
  {
    glfwWindow = GetGlfwWindow();

    shaderProgram = new Shader("./shaders/default.vert", "./shaders/default.frag");

    shaderProgram->Activate();
    glUniform4f(glGetUniformLocation(shaderProgram->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    camera = new Camera(width, height, glm::vec3(50.0f, 0.0f, 2.0f));

    jupiter = new Model("./models/jupiter/scene.gltf");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");
  }

  void Draw()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // FIXME: Skipping camera input on imgui frames not working
    if (!io.WantCaptureMouse)
      camera->Inputs(glfwWindow);

    camera->UpdateMatrix(60.0f, 0.01f, 1000.0f);

    jupiter->Draw(*shaderProgram, *camera);

    /* ImGui::Begin("Settings");
    // TODO: Add settings
    ImGui::End(); */

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void Cleanup()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    shaderProgram->Delete();

    delete shaderProgram;
    shaderProgram = nullptr;

    delete camera;
    camera = nullptr;

    delete jupiter;
    jupiter = nullptr;
  }
};

Application *CreateApplication()
{
  return new App();
}