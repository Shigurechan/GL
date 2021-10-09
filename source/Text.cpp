#include "../header/Text.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <uchar.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H


#include "../header/Window.hpp"
#include "../header/Init.hpp"
#include "../header/Shader.hpp"
#include "../header/Render.hpp"
#include "../header/Camera.hpp"
#include "../header/Resource.hpp"


// ##################################### コンストラクタ ##################################### 
FrameWork::D2::Text::Text() : FrameWork::D2::Render()
{

    //シェーダー読み込み
	shader->Input(FrameWork::LoadShader("Shader/2D/BasicText_2D.vert")->data(),FrameWork::LoadShader("Shader/2D/BasicText_2D.frag")->data());

    vertex = FrameWork::Camera::getVertexAttribute();
    text.clear();

    //頂点	
    GLint attrib = shader->getAttribLocation("vertexPosition");
    glEnableVertexAttribArray(attrib);
    glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(FrameWork::D2::VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
    shader->setBindAttribLocation("vertexPosition");

    //UV
    attrib = shader->getAttribLocation("vertexUV");
    glEnableVertexAttribArray(attrib);
    glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(FrameWork::D2::VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
    shader->setBindAttribLocation("vertexUV");
    
}

// ##################################### wchar_t型の文字列を取得 ##################################### 
std::vector<wchar_t> FrameWork::D2::Text::getWchar_t(const char* str)
{
    std::vector<wchar_t> newText(0);

    int i = 0, j = 0, f = 0;
    for (i = 0, j = 0; str[j] != '\0'; i++, j += f)
    {
        wchar_t t;
        f = (int)mbrtowc(&t, &str[j], (size_t)MB_CUR_MAX, nullptr);
        newText.push_back(t);
    }

    newText.push_back(L'\0');

    return newText;
}

// ##################################### 固定長文字列　描画 ##################################### 
void FrameWork::D2::Text::Draw(glm::vec2 pos)
{
    RenderString(pos);
}

// ##################################### 描画文字 設定 ##################################### 
void FrameWork::D2::Text::setString( const byte ps, const glm::lowp_u8vec4 c, const char* args,...)
{
    text.clear();

    char buf[1024] = { '\0' };

    va_list va;
    va_start(va,args);
    vsprintf(buf,args,va);
    va_end(va);

    color = c;      //色
    pixelSize = ps; //ピクセルサイズ
    std::vector<wchar_t> wc = getWchar_t(buf);  //wchar_t型　取得
    setTexture(wc,text);                        //テクスチャ　設定
}


// ##################################### テクスチャ　設定 ##################################### 
void FrameWork::D2::Text::setTexture(const std::vector<wchar_t>& wc, std::vector<Character>& text)
{
    text.clear();
    FT_Face face = LoadFont("Font/PressStart2P.ttf");
    
    for (std::vector<wchar_t>::const_iterator itr = wc.begin(); itr != wc.end(); itr++)
    {
    
        FT_Error err = FT_Set_Pixel_Sizes(face, 0, pixelSize);
        if( err != 0)
        {
            std::cerr<< "Error: FT_Set_Pixel_Sizes: " << err <<std::endl;
			assert(0);

        }

        err = FT_Load_Glyph(face, FT_Get_Char_Index(face, *itr), FT_LOAD_RENDER);
        if(err != 0)
        {
            std::cerr<< "Error: FT_Load_Glyph: " <<err<<std::endl;
			assert(0);

        }

        Character ch =
        {
            0,
            glm::lowp_u8vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::lowp_u8vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned short)face->glyph->advance.x,
            *itr,
        };

        glGenTextures(1, &ch.textureID);
        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        //テクスチャタイプを設定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        text.push_back(ch);
    }    
}



// ##################################### 文字列を描画 ##################################### 
void FrameWork::D2::Text::RenderString(glm::vec2 pos)
{
    if (text.size() > 0)
    {     

        //色をRGBにして位置を反転
        int y = pos.y;
        for (std::vector<Character>::const_iterator itr = text.begin(); itr->character != L'\0'; itr++)
        {

            pos.y = FrameWork::windowContext->getSize().y - y - pixelSize;

#define SCALE 1.0f  //文字の大きさ

            float xpos = pos.x + itr->bearing.x * SCALE;
            float ypos = pos.y - (itr->size.y - itr->bearing.y) * SCALE;

            float w = itr->size.x * SCALE;
            float h = itr->size.y * SCALE;
            
            vertex->resize(6);
            vertex->at(0).position[0] = xpos;
            vertex->at(0).position[1] = ypos + h;
            vertex->at(0).uv[0] = 0.0f;
            vertex->at(0).uv[1] = 0.0f;

            vertex->at(1).position[0] = xpos;
            vertex->at(1).position[1] = ypos;
            vertex->at(1).uv[0] = 0.0f;
            vertex->at(1).uv[1] = 1.0f;

            vertex->at(2).position[0] = xpos + w;
            vertex->at(2).position[1] = ypos;
            vertex->at(2).uv[0] = 1.0f;
            vertex->at(2).uv[1] = 1.0f;

            vertex->at(3).position[0] = xpos;
            vertex->at(3).position[1] = ypos + h;
            vertex->at(3).uv[0] = 0.0f;
            vertex->at(3).uv[1] = 0.0f;

            vertex->at(4).position[0] = xpos + w;
            vertex->at(4).position[1] = ypos;
            vertex->at(4).uv[0] = 1.0f;
            vertex->at(4).uv[1] = 1.0f;

            vertex->at(5).position[0] = xpos + w;
            vertex->at(5).position[1] = ypos + h;
            vertex->at(5).uv[0] = 1.0f;
            vertex->at(5).uv[1] = 0.0f;



            shader->setEnable();

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBindTexture(GL_TEXTURE_2D, itr->textureID);

            glBufferSubData(GL_ARRAY_BUFFER, 0, vertex->size() * sizeof(FrameWork::D2::VertexAttribute), vertex->data());

            shader->setUniform4f("uFragment", FrameWork::GetGlColor(color));
            shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::windowContext->getSize().x, 0.0f, FrameWork::windowContext->getSize().y));

            glDrawArrays(GL_TRIANGLES, 0, vertex->size());

            //バインド解除
	        glBindVertexArray(0);
	        glBindBuffer(GL_ARRAY_BUFFER, 0);

	        glBindTexture(GL_TEXTURE_2D, 0);
	
            shader->setDisable();


            pos.x += ((itr->advance >> 6) * SCALE); //次のグリフに進める

#undef SCALE
        }
    }
}



// ##################################### デストラクタ ##################################### 
FrameWork::D2::Text::~Text()
{
        
}