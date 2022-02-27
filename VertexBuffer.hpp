#ifndef VERTEXBUFFER_CLASS_H
#define VERTEXBUFFER_CLASS_H

#include "include/glm/glm.hpp"
#include "include/glad/glad.h"
#include <vector>

struct Vertex
{
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec3 color;
  glm::vec2 textureUV;
};

class VertexBuffer
{
public:
  GLuint ID;
  VertexBuffer(std::vector<Vertex> &vertices);
  VertexBuffer(std::vector<glm::mat4> &matrices4);

  void Bind();
  void Unbind();
  void Delete();
};

#endif