#ifndef ___MODEL_HPP_
#define ___MODEL_HPP_

#include <string>
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>


#include "VertexData.hpp"
#include "Shader.hpp"
#include "Transform.hpp"

namespace FrameWork
{
      namespace D3
      {

            typedef struct Texture_
            {
                  unsigned int id;
                  std::string type;
                  aiString path;
            }Texture;


            class Mesh : public Transform
            {
            private:

                  std::vector<VertexAttribute> vertex;
                  std::vector<unsigned int> index;
                  std::vector<Texture>      texture;

                  unsigned int VAO, VBO, EBO;

                  Shader shader;
            public:

                  Mesh(std::vector<VertexAttribute> ver, std::vector<unsigned int> idx, std::vector<Texture> tex);
                  void SetUp();
                  void Draw();
            };



            class Model 
            {
            public:
                  Model(const char *path);
                  void Draw(glm::vec3 pos);	

            private:
                  // model data
                  std::vector<Mesh> mesh;
                  std::string directory;
                  std::vector<Texture> textures_loaded;

                  void loadModel(const char *path);
                  void processNode(aiNode *node, const aiScene *scene);
                  Mesh processMesh(aiMesh *m, const aiScene *scene);
                  std::vector<FrameWork::D3::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,std::string typeName);
                  unsigned int TextureFromFile(const char *path, const std::string &directory);



            };



      }
}
#endif
