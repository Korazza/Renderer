#ifndef MODEL_HPP
#define MODEL_HPP

#include "include/json/json.hpp"

#include "Mesh.hpp"

using json = nlohmann::json;

class Model
{
private:
  const char *file;
  std::vector<unsigned char> data;
  json JSON;
  unsigned int instancing;
  std::vector<Mesh> meshes;
  std::vector<glm::vec3> translationsMeshes;
  std::vector<glm::quat> rotationsMeshes;
  std::vector<glm::vec3> scalesMeshes;
  std::vector<glm::mat4> matricesMeshes;
  std::vector<glm::mat4> instanceMatrix;
  std::vector<std::string> loadedTexturesName;
  std::vector<Texture> loadedTextures;

private:
  void loadMesh(unsigned int meshIndex);

  void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

  std::vector<unsigned char> getData();

  std::vector<float> getFloats(json accessor);
  std::vector<GLuint> getIndices(json accessor);
  std::vector<Texture> getTextures();

  std::vector<Vertex> assembleVertices(
      std::vector<glm::vec3> positions,
      std::vector<glm::vec3> normals,
      std::vector<glm::vec2> textureUVs);

  std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
  std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
  std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);

public:
  Model(const char *file,
        unsigned int instancing = 1,
        std::vector<glm::mat4> instanceMatrix = {});

  void Draw(
      Shader &shader,
      Camera &camera,
      glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
      glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
      glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
};

#endif