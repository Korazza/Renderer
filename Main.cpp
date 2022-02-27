#include <iostream>
#include <math.h>
#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_glfw.h"
#include "include/imgui/imgui_impl_opengl3.h"

#include "Model.hpp"

const unsigned int width{1000};
const unsigned int height{1000};
std::string title{"OpenGL Test"};

unsigned int samples{8};

float gammaValue{2.2f};

float rectangleVertices[]{
    1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 1.0f};

float randf()
{
  return -1.0f + (rand() / (RAND_MAX / 2.0f));
}

int main()
{
  if (!glfwInit())
    return 1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window{glfwCreateWindow(width, height, title.c_str(), NULL, NULL)};
  if (!window)
  {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  gladLoadGL();

  glViewport(0, 0, width, height);

  Shader shaderProgram("./shaders/default.vert", "./shaders/default.frag");
  Shader framebufferProgram("./shaders/framebuffer.vert", "./shaders/framebuffer.frag");

  glm::vec4 lightColor{glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)};
  glm::vec3 lightPos{glm::vec3(0.5f, 0.5f, 0.5f)};

  shaderProgram.Activate();
  glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
  glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
  framebufferProgram.Activate();
  glUniform1i(glGetUniformLocation(framebufferProgram.ID, "screenTexture"), 0);
  glUniform1f(glGetUniformLocation(framebufferProgram.ID, "gamma"), gammaValue);

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_MULTISAMPLE);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  glFrontFace(GL_CCW);

  Camera camera(width, height, glm::vec3(50.0f, 0.0f, 2.0f));

  Model jupiter("./models/jupiter/scene.gltf");

  unsigned int rectVAO, rectVBO;
  glGenVertexArrays(1, &rectVAO);
  glGenBuffers(1, &rectVBO);
  glBindVertexArray(rectVAO);
  glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

  unsigned int FBO;
  glGenFramebuffers(1, &FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);

  unsigned int framebufferTexture;
  glGenTextures(1, &framebufferTexture);
  glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture);
  glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB16F, width, height, GL_TRUE);
  glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture, 0);

  unsigned int RBO;
  glGenRenderbuffers(1, &RBO);
  glBindRenderbuffer(GL_RENDERBUFFER, RBO);
  glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

  auto FBOStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (FBOStatus != GL_FRAMEBUFFER_COMPLETE)
    std::cerr << "Framebuffer error: " << FBOStatus << std::endl;

  unsigned int postProcessingFBO;
  glGenFramebuffers(1, &postProcessingFBO);
  glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFBO);

  unsigned int postProcessingTexture;
  glGenTextures(1, &postProcessingTexture);
  glBindTexture(GL_TEXTURE_2D, postProcessingTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, postProcessingTexture, 0);

  FBOStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (FBOStatus != GL_FRAMEBUFFER_COMPLETE)
    std::cerr << "Post-Processing Framebuffer error: " << FBOStatus << std::endl;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io{ImGui::GetIO()};
  (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  double previousTime{0.0};
  double currentTime{0.0};
  double timeDiff;
  unsigned int counter{0};

  while (!glfwWindowShouldClose(window))
  {
    currentTime = glfwGetTime();
    timeDiff = currentTime - previousTime;
    counter++;
    if (timeDiff >= 1.0 / 30.0)
    {
      std::string fps{std::to_string((1.0 / timeDiff) * counter)};
      std::string frameMs{std::to_string((timeDiff / counter) * 1000)};
      std::string fpsInfo{fps + "fps - " + frameMs + "ms"};
      glfwSetWindowTitle(window, (title + " " + fpsInfo).c_str());
      previousTime = currentTime;
      counter = 0;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glClearColor(pow(0.07f, gammaValue), pow(0.13f, gammaValue), pow(0.17f, gammaValue), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (!io.WantCaptureMouse)
      camera.Inputs(window);
    camera.updateMatrix(45.0f, 0.1f, 1000.0f);

    jupiter.Draw(shaderProgram, camera);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, postProcessingFBO);
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    framebufferProgram.Activate();
    glBindVertexArray(rectVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, postProcessingTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    ImGui::Begin("Settings");
    ImGui::Text("YYAYAYAYAYAY");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  shaderProgram.Delete();
  glDeleteFramebuffers(1, &FBO);
  glDeleteFramebuffers(1, &postProcessingFBO);

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}