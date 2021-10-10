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


FrameWork::D3::Mesh::Mesh(std::vector<VertexAttribute> ver, std::vector<unsigned int> idx, std::vector<Texture> tex)
{
      this->vertex = ver;
      this->index = idx;
      this->texture = tex;
//      printf("ううううう\n");

	shader.Input(FrameWork::LoadShader("Shader/3D/BasicMono_3D.vert")->data(), FrameWork::LoadShader("Shader/3D/BasicMono_3D.frag")->data());

      SetUp();

}



void FrameWork::D3::Mesh::Draw()
{
  //    printf("ららら\n");

      shader.setEnable();

//      printf("Mesh::Draw()\n");
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

  //    printf("ららら\n");



	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexAttribute) * vertex.size(), vertex.data());

	//Transform	
	setPosition(glm::vec3(0,0,-20));    //座標
	setScale(glm::vec3(1,1,1));         //スケール
	setRotate(glm::vec3(0,0,0),0);	//回転

	//描画
      //printf("GGGGGG\n");

	shader.setUniformMatrix4fv("uTranslate",getMatTranslation());
      printf("AAAAAAAAAA\n");
	shader.setUniformMatrix4fv("uRotate", getMatRotate());
	shader.setUniformMatrix4fv("uScale", getMatScale());

	shader.setUniform4f("uFragment", glm::vec4(0,0,1,1));
	shader.setUniformMatrix4fv("uViewProjection", FrameWork::Camera::getViewProjection());

      for(unsigned int i = 0; i < texture.size(); i++)
      {
            glBindTexture(GL_TEXTURE_2D, texture[i].id);
            glActiveTexture(GL_TEXTURE0 + i);
      }

      //glActiveTexture(GL_TEXTURE0);
      glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT, 0);

      


	//バインド解除
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader.setDisable();
}









void FrameWork::D3::Mesh::SetUp()
{
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glGenBuffers(1, &EBO);

      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);


      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), 
                  &index[0], GL_STATIC_DRAW);


      // vertex positions
	GLint attrib = shader.getAttribLocation("vertexPosition");
      glEnableVertexAttribArray(attrib);	
      glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(VertexAttribute), &vertex[0], GL_STATIC_DRAW);  
      glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)0);
      
      // vertex texture coords
      attrib = shader.getAttribLocation("vertexUV");
      glEnableVertexAttribArray(attrib);	
      glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(VertexAttribute), &vertex[0], GL_STATIC_DRAW);  
      glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(sizeof(GLfloat) * 3));

      // vertex normals
      attrib = shader.getAttribLocation("vertexNormal");
      glEnableVertexAttribArray(attrib);	
      glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(VertexAttribute), &vertex[0], GL_STATIC_DRAW);  
      glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(sizeof(GLfloat) * 5));

      printf("ららら\n");

      //glBindVertexArray(0);
}



FrameWork::D3::Model::Model(const char *path)
{
      loadModel(path);
}

void FrameWork::D3::Model::processNode(aiNode *node, const aiScene *scene)
{
      //printf("node->mNumMeshes: %d\n",node->mNumMeshes);

      for(unsigned int i = 0;  i< node->mNumMeshes; i++)
      {
            aiMesh *m = scene->mMeshes[node->mMeshes[i]];
            mesh.push_back(processMesh(m,scene));
      }


      //printf("node->mNumChildren: %d\n",node->mNumChildren);

      for(unsigned int i = 0;  i< node->mNumChildren; i++)
      {
            processNode(node->mChildren[i],scene);
      }


}

void FrameWork::D3::Model::loadModel(const char *path)
{
      Assimp::Importer import;
      const aiScene *scene = import.ReadFile(path,aiProcess_Triangulate | aiProcess_FlipUVs);

      if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
      {
            std::cerr<<"ERROR::ASIMP: " << import.GetErrorString() <<std::endl;
            assert(0);
      }

      std::string str(path);

      directory = str.substr(0,str.find_last_of('/'));

//      printf("ああああ\n");

      processNode(scene->mRootNode, scene);      
      //printf("うううううう\n");
}



FrameWork::D3::Mesh FrameWork::D3::Model::processMesh(aiMesh *m, const aiScene *scene)
{
      // data to fill
      std::vector<VertexAttribute> ver;
      std::vector<unsigned int> idx;
      std::vector<Texture> tex;

      // walk through each of the mesh's vertices
      for(unsigned int i = 0; i < m->mNumVertices; i++)
      {
            VertexAttribute vert;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
  //          printf("てててててててて\n");
            vert.position[0] = m->mVertices[i].x;
            vert.position[1] = m->mVertices[i].y;
            vert.position[2] = m->mVertices[i].z;

            // normals
            if (m->HasNormals() == true)
            {
                  vert.normal[0] = m->mNormals[i].x;
                  vert.normal[1] = m->mNormals[i].y;
                  vert.normal[2] = m->mNormals[i].z;
                  
            }

 //     printf("ええええ\n");

            // texture coordinates
            if(m->mTextureCoords != NULL) // does the m contain texture coordinates?
            {
                  glm::vec2 vec;
                  // a vert can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                  // use models where a vert can have multiple texture coordinates so we always take the first set (0).
                  vert.uv[0] = m->mTextureCoords[0][i].x; 
                  vert.uv[1] = m->mTextureCoords[0][i].y;

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
                  vert.uv[0] = 0.0f;
                  vert.uv[1] = 0.0f;

            }
            ver.push_back(vert);
//            printf("yoyoyoyoyoyo\n");
      }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      
/*
      for(unsigned int i = 0; i < m->mNumFaces; i++)
      {
      printf(" いいいいいい\n");

            aiFace face = m->mFaces[i];
      printf("ああああああ\n");
            
            for(unsigned int j = 0; j < face.mNumIndices; j++)
            {
                  idx.push_back(face.mIndices[j]);        
            }

      }
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //printf("っっっっっっっ\n");
      // process materials
      aiMaterial* material = scene->mMaterials[m->mMaterialIndex];    
      // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
      // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
      // Same applies to other texture as the following list summarizes:
      // diffuse: texture_diffuseN
      // specular: texture_specularN
      // normal: texture_normalN
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

    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

      if (data)
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
            printf("っっっっ\n");

            glBindTexture(GL_TEXTURE_2D, textureID);

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);
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
          printf("ああああ\n");
        mesh[i].Draw();
  //        printf("いいいい\n");

    }
}
