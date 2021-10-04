#ifndef ___RESOURCE_HPP_
#define ___RESOURCE_HPP_

#include <vector>
#include <memory>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H



#include "Help.hpp"

namespace FrameWork
{
	extern FT_Library ft;


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
      std::shared_ptr<std::vector<GLchar>> LoadShader(const char* fileName);
      SoundFile LoadSound(const char* fileName);
      FT_Face LoadFont(const char* fileName);

}


#endif
