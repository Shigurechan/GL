#include <iostream>
#include "../header/Text.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <uchar.h>
#include "../header/Window.hpp"
#include "../header/Init.hpp"
#include "../header/Shader.hpp"
#include <iostream>
#include <vector>

#include "../header/Render.hpp"
#include "../header/Camera.hpp"


// ##################################### コンストラクタ ##################################### 
FrameWork::Text::Text() : FrameWork::Render_2D()
{
    
    fixedLength = std::make_unique<std::vector<String>>(0);    //　固定長文字列

    //シェーダー読み込み
    shader = std::make_unique<FrameWork::Shader>();
    
    vertex = FrameWork::Camera_2D::getVertexAttribute();
    vertex->resize(6);

    //頂点	
    GLint attrib = shader->getAttribLocation("vertexPosition");
    glEnableVertexAttribArray(attrib);
    glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
    shader->setBindAttribLocation("vertexPosition");

    //UV
    attrib = shader->getAttribLocation("vertexUV");
    glEnableVertexAttribArray(attrib);
    glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
    shader->setBindAttribLocation("vertexUV");
    
}

// ##################################### wchar_t型の文字列を取得 ##################################### 
std::vector<wchar_t> FrameWork::Text::getWchar_t(const char* str)
{
    std::vector<wchar_t> newText(0);

    int i, j, f;
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
void FrameWork::Text::DrawString(glm::vec2 pos,byte n)
{

    RenderString(pos,fixedLength->at(n).text);
}


// ##################################### テクスチャ　設定 ##################################### 
void FrameWork::Text::setTexture(const std::vector<wchar_t>& wc, std::shared_ptr<std::vector<Character>>& text, const glm::lowp_u8vec4 color, const byte pixelSize)
{
    for (std::vector<wchar_t>::const_iterator itr = wc.begin(); itr != wc.end(); itr++)
    {
        FT_Face face;// = Resource::getFont((Resource::Asset)font);
        FT_Set_Pixel_Sizes(face, 0, pixelSize);
        FT_Load_Glyph(face, FT_Get_Char_Index(face, *itr), FT_LOAD_RENDER);
        
        Character ch =
        {
            0,
            glm::lowp_u8vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::lowp_u8vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned short)face->glyph->advance.x,
            *itr,
            color,
            pixelSize
        };

        glGenTextures(1, &ch.textureID);
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        glActiveTexture(GL_TEXTURE0);

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

        text->push_back(ch);
    }    
}



// ##################################### 文字列を描画 ##################################### 
void FrameWork::Text::RenderString(glm::vec2 pos,const std::shared_ptr<std::vector<Character>> character)
{
    if (character->size() > 0)
    {     
        vertex->resize(6);

        //色をRGBにして位置を反転
        int y = pos.y;
        for (std::vector<Character>::const_iterator itr = character->begin(); itr->character != '\0'; itr++)
        {
            pos.y = FrameWork::windowContext->getSize().y - y - itr->pixelSize;

#define SCALE 1.0f  //文字の大きさ

            float xpos = pos.x + itr->bearing.x * SCALE;
            float ypos = pos.y - (itr->size.y - itr->bearing.y) * SCALE;

            float w = itr->size.x * SCALE;
            float h = itr->size.y * SCALE;

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

            glBufferSubData(GL_ARRAY_BUFFER, 0, vertex->size() * sizeof(VertexAttribute), vertex->data());

            shader->setUniform4f("uFragment", GetGlColor((glm::vec4)itr->color));
            shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::windowContext->getSize().x, 0.0f, FrameWork::windowContext->getSize().y));

            glBindTexture(GL_TEXTURE_2D, itr->textureID);

            glDrawArrays(GL_TRIANGLES, 0, vertex->size());

            glBindTexture(GL_TEXTURE_2D, 0);

            pos.x += ((itr->advance >> 6) * SCALE); //次のグリフに進める

#undef SCALE
        }
    }
}



// ##################################### デストラクタ ##################################### 
FrameWork::Text::~Text()
{
    
    //FT_Done_FreeType(ft);
}


