#include "../header/Model.hpp"

#include <iostream>
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


FrameWork::D3::Mesh::Mesh(std::vector<VertexAttribute> ver, std::vector<unsigned int> idx, std::vector<Texture> tex) : Transform()
{
      this->vertex = ver;     //頂点
      this->index = idx;      //インデックス
      this->texture = tex;    //テクスチャ

      printf("this->vertex: %d\n",this->vertex.size());
      printf("this->index: %d\n",this->index.size());
      printf("this->texture: %d\n\n",this->texture.size());


//printf("あああ\n");
	shader.Input(FrameWork::LoadShader("Shader/3D/BasicMono_3D.vert")->data(), FrameWork::LoadShader("Shader/3D/BasicMono_3D.frag")->data());
//printf("いいい\n");

      SetUp();
}



void FrameWork::D3::Mesh::Draw()
{
      shader.setEnable();

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexAttribute) * vertex.size(), vertex.data());
//      printf("ら\n");

	//Transform	
	setPosition(glm::vec3(0,0,-20));    //座標
	setScale(glm::vec3(10,10,10));         //スケール
	setRotate(glm::vec3(0,0,0),0);	//回転

	//描画
printf("いいい\n");
	shader.setUniformMatrix4fv("uTranslate",getMatTranslation());
printf("あああ\n");
	shader.setUniformMatrix4fv("uRotate", getMatRotate());
	shader.setUniformMatrix4fv("uScale", getMatScale());
	shader.setUniform4f("uFragment", glm::vec4(0,0,1,1));
	shader.setUniformMatrix4fv("uViewProjection", FrameWork::Camera::getViewProjection());

      for(unsigned int i = 0; i < texture.size(); i++)
      {
            //glBindTexture(GL_TEXTURE_2D, texture[i].id);
            //glActiveTexture(GL_TEXTURE0 + i);
      }

      //glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT, 0);
      glDrawArrays(GL_TRIANGLES,0,vertex.size());

	//バインド解除
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);

	shader.setDisable();
}

void FrameWork::D3::Mesh::SetUp()
{
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      //glGenBuffers(1, &EBO);


      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);

      //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

      //glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int),index.data(), GL_DYNAMIC_DRAW);
      glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(VertexAttribute), vertex.data(), GL_DYNAMIC_DRAW);  

      // vertex positions
	GLint attrib = shader.getAttribLocation("vertexPosition");
      glEnableVertexAttribArray(attrib);	
      glVertexAttribPointer(attrib, 1, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)0);
      shader.setBindAttribLocation("vertexPosition");

      // vertex texture coords
      //attrib = shader.getAttribLocation("vertexUV");
      //glEnableVertexAttribArray(attrib);	
      //glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(sizeof(GLfloat) * 3));
//printf("ららら\n");
      // vertex normals
      //attrib = shader.getAttribLocation("vertexNormal");
      //glEnableVertexAttribArray(attrib);	
      //glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(sizeof(GLfloat) * 5));


      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      
}



FrameWork::D3::Model::Model(const char *path)
{
      loadModel(path);
}

void FrameWork::D3::Model::processNode(aiNode *node, const aiScene *scene)
{

      for(unsigned int i = 0;  i< node->mNumMeshes; i++)
      {
            aiMesh *m = scene->mMeshes[node->mMeshes[i]];
            mesh.push_back(processMesh(m,scene));
      }

      for(unsigned int i = 0;  i< node->mNumChildren; i++)
      {
            processNode(node->mChildren[i],scene);
      }
}

void FrameWork::D3::Model::loadModel(const char *path)
{
      Assimp::Importer import;
      const aiScene *scene = import.ReadFile(path,aiProcess_Triangulate | aiProcess_FlipUVs);

      if(scene == NULL)
      {
            std::cerr<<"ERROR::ASIMP: " << import.GetErrorString() <<std::endl;
            assert(0);
      }

      std::string str(path);

      directory = str.substr(0,str.find_last_of('/'));

      processNode(scene->mRootNode, scene);      
}



FrameWork::D3::Mesh FrameWork::D3::Model::processMesh(aiMesh *m, const aiScene *scene)
{
      // data to fill
      std::vector<VertexAttribute> ver(0);
      std::vector<unsigned int> idx(0);
      std::vector<Texture> tex(0);
      

      for(unsigned int i = 0; i < m->mNumVertices; i++)
      {
            VertexAttribute vert;
            glm::vec3 vector; 
            vert.position[0] = m->mVertices[i].x;
            vert.position[1] = m->mVertices[i].y;
            vert.position[2] = m->mVertices[i].z;

            // normals
            if (m->HasNormals() == true)
            {
                  //vert.normal[0] = m->mNormals[i].x;
                  //vert.normal[1] = m->mNormals[i].y;
                  //vert.normal[2] = m->mNormals[i].z;
                  
            }

            // texture coordinates
            if(m->mTextureCoords != NULL)
            {
                  glm::vec2 vec;
                  //vert.uv[0] = m->mTextureCoords[0][i].x; 
                  //vert.uv[1] = m->mTextureCoords[0][i].y;

      /*            
                  // tangent
                  vector.x = m->mTangents[i].x;
                  vector.y = m->mTangents[i].y;
                  vector.z = m->mTangents[i].z;
                  //vert.Tangent = vector;

                  // bitangent
                  vector.x = m->mBitangents[i].x;
                  vector.y = m->mBitangents[i].y;
                  vector.z = m->mBitangents[i].z;
                  //vert.Bitangent = vector;
      */
            }
            else
            {
                  //vert.uv[0] = 0.0f;
                  //vert.uv[1] = 0.0f;

            }
            ver.push_back(vert);
      }
     
/*
      for(unsigned int i = 0; i < m->mNumFaces; i++)
      {
            aiFace face = m->mFaces[i];
            
            for(unsigned int j = 0; j < face.mNumIndices; j++)
            {
                  idx.push_back(face.mIndices[j]);        
            }
      }
*/

/*
      printf("ああ %d\n",m->mMaterialIndex);
      // process materials
      aiMaterial* material = scene->mMaterials[m->mMaterialIndex];    
      printf("いいい \n");

      // 1. diffuse maps
      std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
      tex.insert(tex.end(), diffuseMaps.begin(), diffuseMaps.end());
      // 2. specular maps
      std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
      tex.insert(tex.end(), specularMaps.begin(), specularMaps.end());
      // 3. normal maps
      std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
      tex.insert(tex.end(), normalMaps.begin(), normalMaps.end());
      // 4. height maps
      std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
      tex.insert(tex.end(), heightMaps.begin(), heightMaps.end());
      // return a mesh object created from the extracted mesh data

*/
  
     return Mesh(ver, idx, tex);
      
}

std::vector<FrameWork::D3::Texture> FrameWork::D3::Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type,std::string typeName)
{
      std::vector<Texture> texture;

      for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
      {
            aiString str;
            mat->GetTexture(type, i, &str);
            bool skip = false;
            for(unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                  if(std::strcmp(textures_loaded[j].path.data, str.C_Str()) == 0)
                  {
                        texture.push_back(textures_loaded[j]);
                        skip = true; 
                        break;
                  }
            }

            if(!skip)
            {
                  for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
                  {
                        aiString str;
                        mat->GetTexture(type, i, &str);
                        Texture tex;
                        tex.id = TextureFromFile(str.C_Str(), directory);
                        tex.type = typeName;
                        tex.path = str;
                        texture.push_back(tex);
                  }
            }
      }
      return texture;
}


unsigned int FrameWork::D3::Model::TextureFromFile(const char *path, const std::string &directory)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;

//    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

      if (data != NULL)
      {
            GLenum format;

            if (nrComponents == 1)
            {
                  format = GL_RED;
            }
            else if (nrComponents == 3)
            {
                  format = GL_RGB;
            }
            else if (nrComponents == 4)
            {
                  format = GL_RGBA;
            }

/*
            glBindTexture(GL_TEXTURE_2D, textureID);

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);
*/
    }
    else
    {
        std::cerr << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


void FrameWork::D3::Model::Draw(glm::vec3 pos)
{
      for(unsigned int i = 0; i < mesh.size(); i++)
      {
            mesh[i].Draw();
      }
}
