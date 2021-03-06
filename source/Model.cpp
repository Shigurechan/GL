#include "../header/Model.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "../lib/stb/stb_image.h"

#include "../header/Resource.hpp"
#include "../header/Camera.hpp"
#include "../header/Window.hpp"
#include "../header/Camera.hpp"

FrameWork::D3::Object::Object(ObjFile *o, short type) : Render()
{
      renderType = type;
      obj = o; //オブジェクトファイル
}

void FrameWork::D3::Object::setTexture(GLuint tex)
{
     textureID.push_back(tex);
}

void FrameWork::D3::Object::setVertexAttribute(const char *str, int num)
{
      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);

      shader->setVertexAttribute(str, num);

      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void FrameWork::D3::Object::setVertexBuffer()
{
      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);

      glBufferData(GL_ARRAY_BUFFER, obj->attribute.size() * sizeof(VertexAttribute), obj->attribute.data(), GL_STATIC_DRAW); //頂点属性

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
}

void FrameWork::D3::Object::setIndexBuffer()
{
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eao);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj->index.size() * sizeof(unsigned int), obj->index.data(), GL_STATIC_DRAW); //頂点インデックス
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}





void FrameWork::D3::Object::Renderer()
{
      // shader->setEnable();
      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);

      glActiveTexture(GL_TEXTURE0); //テクスチャ有効
      glBindTexture(GL_TEXTURE_2D, textureID.at(0)); // IDバインド
//      glActiveTexture(GL_TEXTURE1); //テクスチャ有効
//      glBindTexture(GL_TEXTURE_2D, textureID.at(1)); // IDバインド

      

      //描画
      shader->setUniformMatrix4fv("uTranslate", getMatTranslation());
      shader->setUniformMatrix4fv("uRotate", getMatRotate());
      shader->setUniformMatrix4fv("uScale", getMatScale());
      shader->setUniformMatrix4fv("uViewProjection", FrameWork::Camera::getViewProjection());

      if (obj->index.size() > 0)
      {
            // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eao);
            // glDrawElements(GL_TRIANGLES, obj->index.size(), GL_UNSIGNED_INT,(void*)0); //描画
            // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      }

      glDrawArrays(GL_TRIANGLES, 0, obj->attribute.size()); //描画

      //バインド解除
      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindTexture(GL_TEXTURE_2D, 0);
  //    glBindTexture(GL_TEXTURE_2D, 1);
      
      // shader->setDisable();
}

FrameWork::D3::Object::~Object()
{
}

// ##################################### .objファイル読み込み #####################################
void FrameWork::D3::LoadObj(const char *fileName, ObjFile &attribute)
{
      ObjFile obj;

      std::vector<int> vertexIndex;
      std::vector<int> uvIndex;
      std::vector<int> normalIndex;

      std::vector<glm::vec3> vertex;
      std::vector<glm::vec2> uv;
      std::vector<glm::vec3> normal;

      FILE *file = fopen(fileName, "r");

      if (file == NULL)
      {
            std::cerr << ".OBJファイルが開けません: " << fileName << std::endl;
            assert(0);
      }
      else
      {
            while (true)
            {
                  char line[500];

                  int res = fscanf(file, "%s", line);

                  if (res == EOF)
                  {
                        break;
                  }

                  if (strcmp(line, "v") == 0)
                  {
                        glm::vec3 vert;
                        fscanf(file, "%f %f %fn", &vert.x, &vert.y, &vert.z);
                        vertex.push_back(vert);
                  }
                  else if (strcmp(line, "vt") == 0)
                  {
                        glm::vec2 u;
                        fscanf(file, "%f %fn", &u.x, &u.y);
                        uv.push_back(u);
                  }
                  else if (strcmp(line, "vn") == 0)
                  {
                        glm::vec3 norm;
                        fscanf(file, "%f %f %fn", &norm.x, &norm.y, &norm.z);
                        normal.push_back(norm);
                  }
                  else if (strcmp(line, "f") == 0)
                  {
                        unsigned int v[3], u[3], n[3];
                        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%dn", &v[0], &u[0], &n[0], &v[1], &u[1], &n[1], &v[2], &u[2], &n[2]);

                        vertexIndex.push_back(v[0]);
                        vertexIndex.push_back(v[1]);
                        vertexIndex.push_back(v[2]);

                        uvIndex.push_back(u[0]);
                        uvIndex.push_back(u[1]);
                        uvIndex.push_back(u[2]);

                        normalIndex.push_back(n[0]);
                        normalIndex.push_back(n[1]);
                        normalIndex.push_back(n[2]);
                  }
            }

            for (unsigned int i = 0; i < vertexIndex.size(); i++)
            {
                  unsigned int vi = vertexIndex[i];
                  unsigned int ui = uvIndex[i];
                  unsigned int ni = normalIndex[i];

                  glm::vec3 v = vertex[vi - 1];
                  glm::vec2 u = uv[ui - 1];
                  glm::vec3 n = normal[ni - 1];

                  VertexAttribute attrib;

                  attrib.position[0] = v.x;
                  attrib.position[1] = v.y;
                  attrib.position[2] = v.z;

                  attrib.uv[0] = u.x;
                  attrib.uv[1] = -u.y;

                  attrib.normal[0] = n.x;
                  attrib.normal[1] = n.y;
                  attrib.normal[2] = n.z;

                  obj.attribute.push_back(attrib);
            }
      }
      attribute = obj;
}
