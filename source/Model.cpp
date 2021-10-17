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

FrameWork::D3::Object::Object(ObjFile o) : Render()
{
      shader->Input(FrameWork::LoadShader("Shader/3D/BasicMono_3D.vert")->data(), FrameWork::LoadShader("Shader/3D/BasicMono_3D.frag")->data());
      obj = o;    //オブジェクトファイル

      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio);

      printf("%d\n",obj.vertexIndex.size());
      printf("%d\n",obj.vertex.size());

      //頂点
      GLint attrib = shader->getAttribLocation("vertexPosition");
      glEnableVertexAttribArray(attrib);
      glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
      shader->setBindAttribLocation("vertexPosition");


      glBufferData(GL_ARRAY_BUFFER, obj.vertex.size() * sizeof(GLfloat) * 11, obj.vertex.data(), GL_STATIC_DRAW);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj.vertexIndex.size() * sizeof(unsigned int), obj.vertexIndex.data(), GL_STATIC_DRAW);

      setRotate(glm::vec3(1, 1, 1),0);   //回転



      //バインド解除
      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void FrameWork::D3::Object::Renderer()
{
      shader->setEnable();
      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio);

      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * obj.vertex.size(), obj.vertex.data());

      //Transform
      setPosition(glm::vec3(0, 0, -50));        //座標
      setScale(glm::vec3(30, 30, 30));          //スケール
      //setRotate(glm::vec3(0, 1, 0),PI /2);    //回転

      //描画
      shader->setUniformMatrix4fv("uTranslate", getMatTranslation());
      shader->setUniformMatrix4fv("uRotate", getMatRotate());
      shader->setUniformMatrix4fv("uScale", getMatScale());
      shader->setUniformMatrix4fv("uViewProjection", FrameWork::Camera::getViewProjection());
      shader->setUniform4f("uFragment", GetGlColor(glm::vec4(0, 255, 0, 255)));

      //glDrawArrays(GL_TRIANGLES, 0, obj.vertex.size()); //描画
      glDrawElements(GL_TRIANGLES, obj.vertexIndex.size(), GL_UNSIGNED_INT,(void*)0); //描画


      //バインド解除
      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      shader->setDisable();
}

FrameWork::D3::Object::~Object()
{
      
}

// ##################################### .objファイル読み込み #####################################
void FrameWork::D3::LoadObj(const char *fileName, ObjFile &attribute)
{
      ObjFile obj;

      std::vector<float> vertexIndex;
      std::vector<glm::vec3> vertex;

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
                        obj.uv.push_back(u);
                  }
                  else if (strcmp(line, "vn") == 0)
                  {

                        glm::vec3 norm;
                        fscanf(file, "%f %f %fn", &norm.x, &norm.y, &norm.z);
                        obj.normal.push_back(norm);
                  }
                  else if (strcmp(line, "f") == 0)
                  {

                        std::string vertex1, vertex2, vertex3;
                        unsigned int v[3], u[3], n[3];
                        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%dn", &v[0], &u[0], &n[0], &v[1], &u[1], &n[1], &v[2], &u[2], &n[2]);
                        if (matches != 9)
                        {
                              printf("File can't be read by our simple parser : ( Try exporting with other optionsn");
                              assert(0);
                        }

                        vertexIndex.push_back(v[0]);
                        vertexIndex.push_back(v[1]);
                        vertexIndex.push_back(v[2]);
                        
                        obj.vertexIndex.push_back(v[0]);
                        obj.vertexIndex.push_back(v[1]);
                        obj.vertexIndex.push_back(v[2]);

                        obj.uvIndex.push_back(u[0]);
                        obj.uvIndex.push_back(u[1]);
                        obj.uvIndex.push_back(u[2]);

                        obj.normalIndex.push_back(n[0]);
                        obj.normalIndex.push_back(n[1]);
                        obj.normalIndex.push_back(n[2]);
                  }
            }
      }

      for (int i = 0; i < vertexIndex.size(); i++)
      {
            int vert = vertexIndex[i];

            obj.vertex.push_back(vertex[vert - 1]);
//            printf("%f %f %f \n", obj.vertex.at(i).x, obj.vertex.at(i).y, obj.vertex.at(i).z);
      }

      //printf("%d\n\n",obj.vertex.size());

      attribute = obj;
}
