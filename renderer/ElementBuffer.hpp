#ifndef ELEMENTBUFFER_HPP
#define ELEMENTBUFFER_HPP

#include "include/glad/glad.h"
#include <vector>

class ElementBuffer
{
public:
  GLuint ID;

public:
  ElementBuffer(std::vector<GLuint> &indices);

  void Bind();

  void Unbind();

  void Delete();
};

#endif