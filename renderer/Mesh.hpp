#ifndef MESH_HPP
#define MESH_HPP

#include <string>

#include "VertexArray.hpp"
#include "ElementBuffer.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    VertexArray VAO;
    unsigned int instancing;

public:
    Mesh(
        std::vector<Vertex> &vertices,
        std::vector<GLuint> &indices,
        std::vector<Texture> &textures,
        unsigned int instancing = 1,
        std::vector<glm::mat4> instanceMatrix = {});

    void Draw(
        Shader &shader,
        Camera &camera,
        glm::mat4 matrix = glm::mat4(1.0f),
        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
};

#endif