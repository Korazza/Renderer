#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(std::vector<Vertex> &vertices)
{
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ARRAY_BUFFER, ID);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(std::vector<glm::mat4> &matrices4)
{
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ARRAY_BUFFER, ID);
  glBufferData(GL_ARRAY_BUFFER, matrices4.size() * sizeof(glm::mat4), matrices4.data(), GL_STATIC_DRAW);
}

void VertexBuffer::Bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::Unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Delete()
{
  glDeleteBuffers(1, &ID);
}