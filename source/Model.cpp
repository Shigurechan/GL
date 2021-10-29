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

FrameWork::D3::Object::Object(ObjFile o, const char *vert, const char *frag) : Render()
{
      shader->Input(FrameWork::LoadShader(vert)->data(), FrameWork::LoadShader(frag)->data());
      obj = o; //オブジェクトファイル


      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eao);

      //座標
      GLint attrib = shader->getAttribLocation("vertexPosition");
      glEnableVertexAttribArray(attrib);
      glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
      shader->setBindAttribLocation("vertexPosition");

      /*
            //UV
            attrib = shader->getAttribLocation("vertexUV");
            glEnableVertexAttribArray(attrib);
            glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
            shader->setBindAttribLocation("vertexUV");
      */

      //法線
      attrib = shader->getAttribLocation("vertexNormal");
      glEnableVertexAttribArray(attrib);
      glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(5 * sizeof(GLfloat)));
      shader->setBindAttribLocation("vertexNormal");

      glBufferData(GL_ARRAY_BUFFER, obj.attribute.size() * sizeof(VertexAttribute), obj.attribute.data(), GL_STATIC_DRAW);    //頂点属性
      //glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj.index.size() * sizeof(unsigned int), obj.index.data(), GL_STATIC_DRAW);       //頂点インデックス


      //      glGenTextures(1, &textureID);		     //テクスチャIDの生成
      //	glBindTexture(GL_TEXTURE_2D, textureID); //IDバインド

      /*
            //テクスチャ生成
            FrameWork::TextureFile file = FrameWork::LoadTexture("Assets/debug_texture.png");

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, file.size.x, file.size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, file.fileData);

            // テクスチャの補間設定
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glGenerateMipmap(GL_TEXTURE_2D);
      */

      //バインド解除
      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      //	glBindTexture(GL_TEXTURE_2D, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void FrameWork::D3::Object::Renderer()
{
      // shader->setEnable();
      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eao);
      //	glBindTexture(GL_TEXTURE_2D, textureID);        //IDバインド

      // glActiveTexture(GL_TEXTURE0); //テクスチャ有効

      //描画
      shader->setUniformMatrix4fv("uTranslate", getMatTranslation());
      shader->setUniformMatrix4fv("uRotate", getMatRotate());
      shader->setUniformMatrix4fv("uScale", getMatScale());
      shader->setUniformMatrix4fv("uViewProjection", FrameWork::Camera::getViewProjection());

      //glDrawElements(GL_TRIANGLES, obj.index.size(), GL_UNSIGNED_INT,(void*)0); //描画
      glDrawArrays(GL_TRIANGLES, 0, obj.attribute.size()); //描画

      //バインド解除
      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      // glBindTexture(GL_TEXTURE_2D, 0);
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
                  attrib.uv[1] = u.y;

                  attrib.normal[0] = n.x;
                  attrib.normal[1] = n.y;
                  attrib.normal[2] = n.z;
                  
                  obj.attribute.push_back(attrib);
            }
      }
      attribute = obj;
}
