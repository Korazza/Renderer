#ifndef SHADER_HPP
#define SHADER_HPP

#include "include/glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char *filename);

class Shader
{
public:
  GLuint ID;

private:
  void compileErrors(unsigned int shader, const char *type);

public:
  Shader(const char *vertexFile, const char *fragmentFile);

  Shader(const char *vertexFile, const char *fragmentFile, const char *geometryFile);

  void Activate();

  void Delete();
};

#endif