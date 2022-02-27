#ifndef VERTEXARRAY_CLASS_HPP
#define VERTEXARRAY_CLASS_HPP

#include "include/glad/glad.h"

#include "VertexBuffer.hpp"

class VertexArray
{
public:
  GLuint ID;
  VertexArray();

  void LinkAttrib(VertexBuffer &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset);

  void Bind();
  void Unbind();
  void Delete();
};

#endif