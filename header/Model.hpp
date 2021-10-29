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
#include "Render.hpp"
#include "Resource.hpp"

namespace FrameWork
{
      namespace D3
      {
            class Object : public Render
            {
            public: 
                  Object(ObjFile o,const char* vert,const char* frag);
                  ~Object();
                  void Renderer();

            private:
                  void operator = (const Object &o);  //コピー禁止
                  ObjFile obj;
                  GLuint textureID;

            };




            void LoadObj(const char* filename, ObjFile &attribute);


      }
}
#endif
