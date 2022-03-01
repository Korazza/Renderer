#include <iostream>
#include <math.h>
#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_glfw.h"
#include "include/imgui/imgui_impl_opengl3.h"

#include "Application.hpp"
#include "Model.hpp"

unsigned int width{900};
unsigned int height{900};

unsigned int samples{8};

float gammaValue{2.2f};

float rectangleVertices[]{
    1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 1.0f};

GLFWwindow *glfwWindow;
ImGuiIO io;

Shader *shaderProgram{nullptr};
/* Shader *framebufferProgram{nullptr}; */

glm::vec4 lightColor{glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)};
glm::vec3 lightPos{glm::vec3(0.5f, 0.5f, 0.5f)};

Camera *camera{nullptr};

Model *jupiter{nullptr};

/* unsigned int
    rectanglesVAO,
    rectanglesVBO,
    FBO,
    postProcessingFBO,
    RBO,
    framebufferTexture,
    postProcessingTexture; */

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
    /* framebufferProgram = new Shader("./shaders/framebuffer.vert", "./shaders/framebuffer.frag"); */

    shaderProgram->Activate();
    glUniform4f(glGetUniformLocation(shaderProgram->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    camera = new Camera(width, height, glm::vec3(50.0f, 0.0f, 2.0f));

    jupiter = new Model("./models/jupiter/scene.gltf");

    // TODO: Create FrameBuffer
    /* glGenVertexArrays(1, &rectanglesVAO);
    glGenBuffers(1, &rectanglesVBO);
    glBindVertexArray(rectanglesVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rectanglesVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB16F, GetWindowWidth(), GetWindowHeight(), GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, GetWindowWidth(), GetWindowHeight());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    auto FBOStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (FBOStatus != GL_FRAMEBUFFER_COMPLETE)
      std::cerr << "Framebuffer error: " << FBOStatus << std::endl;

    glGenFramebuffers(1, &postProcessingFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFBO);

    glGenTextures(1, &postProcessingTexture);
    glBindTexture(GL_TEXTURE_2D, postProcessingTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, GetWindowWidth(), GetWindowHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, postProcessingTexture, 0);

    FBOStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (FBOStatus != GL_FRAMEBUFFER_COMPLETE)
      std::cerr << "Post-Processing Framebuffer error: " << FBOStatus << std::endl; */

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");
  }

  void Draw()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (!io.WantCaptureMouse)
      camera->Inputs(glfwWindow);
    camera->UpdateMatrix(45.0f, 0.1f, 1000.0f);

    jupiter->Draw(*shaderProgram, *camera);

    /* glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, postProcessingFBO);
    glBlitFramebuffer(0, 0, GetWindowWidth(), GetWindowHeight(), 0, 0, GetWindowWidth(), GetWindowHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    framebufferProgram->Activate();
    glBindVertexArray(rectanglesVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, postProcessingTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6); */

    ImGui::Begin("Settings");
    // TODO: add settings
    ImGui::End();

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

    /* glDeleteFramebuffers(1, &FBO);
    glDeleteFramebuffers(1, &postProcessingFBO);
    framebufferProgram->Delete(); */
  }
};

Application *CreateApplication()
{
  return new App();
}