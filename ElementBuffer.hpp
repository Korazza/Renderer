#ifndef INDEXBUFFER_CLASS_H
#define INDEXBUFFER_CLASS_H

#include "include/glad/glad.h"
#include <vector>

class ElementBuffer
{
public:
  GLuint ID;
  ElementBuffer(std::vector<GLuint> &indices);

  void Bind();
  void Unbind();
  void Delete();
};

#endif