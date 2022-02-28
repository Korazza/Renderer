#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "include/glad/glad.h"
#include "include/stb/stb_image.h"

#include "Shader.hpp"

class Texture
{
public:
  GLuint ID;
  const char *type;
  GLuint unit;

public:
  Texture(const char *image, const char *texType, GLuint slot);

  void texUnit(Shader &shader, const char *uniform, GLuint unit);

  void Bind();

  void Unbind();

  void Delete();
};

#endif