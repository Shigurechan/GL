#include "../header/Resource.hpp"

#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"

//テクスチャをロード
TextureFile LoadTexture(const char* fileName)
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
ShaderFile LoadShader(const char* fileName)
{

      ShaderFile data;

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

            data.fileData = buffer;
      }

      file.close();
      
	
}


SoundFile LoadSound(const char* fileName)
{

}

