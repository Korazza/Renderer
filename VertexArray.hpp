#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "include/glad/glad.h"

#include "VertexBuffer.hpp"

class VertexArray
{
public:
  GLuint ID;

public:
  VertexArray();

  void LinkAttrib(VertexBuffer &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset);

  void Bind();

  void Unbind();

  void Delete();
};

#endif