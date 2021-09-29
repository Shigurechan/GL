#ifndef ___RESOURCE_HPP_
#define ___RESOURCE_HPP_

#include <vector>
#include <memory>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "Help.hpp"



//シェーダーファイル
typedef struct
{
      std::shared_ptr<std::vector<GLchar>> fileData;
}ShaderFile;

//テクスチャファイル
typedef struct
{
      glm::ivec2 size;  //サイズ
      int channel;      //チャンネル数
      byte *fileData;   //ファイルデータ

}TextureFile;


//サウンドファイル
typedef struct
{

}SoundFile;



TextureFile LoadTexture(const char* fileName);
ShaderFile LoadShader(const char* fileName);
SoundFile LoadSound(const char* fileName);





#endif
