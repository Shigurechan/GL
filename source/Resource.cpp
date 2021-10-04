#include "../header/Resource.hpp"

#include <fstream>
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
		std::cerr << "アセットが見つかりません: " << fileName << std::endl;
		assert(0);
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
