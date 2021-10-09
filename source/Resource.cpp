#include "../header/Resource.hpp"

#include <fstream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"

#include <ft2build.h>
#include FT_FREETYPE_H


FT_Library FrameWork::ft;


//テクスチャをロード
FrameWork::TextureFile FrameWork::LoadTexture(const char* fileName)
{
      TextureFile data;
	data.fileData = NULL;      
      data.fileData = stbi_load(fileName,&data.size.x,&data.size.y,&data.channel,0);

	if (data.fileData == NULL)
	{
		std::cerr << "画像が見つかりません: " << fileName << std::endl;
		assert(0);
	}

      return data;

}

//テクスチャ分割ロード
std::vector<FrameWork::TextureFile> FrameWork::LoadTextureSize(glm::ivec2 fileSize,glm::ivec2 imageSize,glm::ivec2 num,const char* fileName)
{
     
      std::vector<FrameWork::TextureFile> data;
      FrameWork::TextureFile image;
      image.fileData = stbi_load(fileName,&image.size.x,&image.size.y,&image.channel,0);

	if (image.fileData == NULL)
	{
		std::cerr << "画像が見つかりません: " << fileName << std::endl;
		assert(0);
	}
      else
      {
            
      }

      return data;
 
}


//シェーダーファイルをロード
std::shared_ptr<std::vector<GLchar>> FrameWork::LoadShader(const char* fileName)
{
      std::ifstream file(fileName, std::ios::binary);
      if (file.fail() == true)
      {
            std::cerr << "シェーダーファイルを読み込めません: " << fileName << std::endl;

            file.close();
            assert(0);
      }
      else
      {	
            std::shared_ptr<std::vector<GLchar>> buffer = std::make_shared<std::vector<GLchar>>(0);
            file.seekg(0L, std::ios::end);
            GLsizei length = static_cast<GLsizei>(file.tellg());
            buffer->resize(length + 1);
            file.seekg(0L, std::ios::beg);
            file.read(buffer->data(), length);
            buffer->at(length) = ('\0');
            file.close();

            return buffer;      
      }

      file.close();
      
}


FrameWork::SoundFile FrameWork::LoadSound(const char* fileName)
{
      
}

FT_Face FrameWork::LoadFont(const char* fileName)
{
      
      FT_Face face;

      FT_Error error = FT_New_Face(FrameWork::ft,fileName, 0, &face);
      if (error != 0)
      {
            std::cerr << "FreeType フォントを読み込めません: " << error << std::endl;
            assert(0);
      }
      else
      {
            return face;
      }
}
