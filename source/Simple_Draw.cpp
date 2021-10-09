#include "../header/Simple_Draw.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>

#include "../lib/stb/stb_image.h"

#include "../header/Window.hpp"
#include "../header/Resource.hpp"
#include "../header/Init.hpp"
#include "../header/Shader.hpp"
#include "../header/Help.hpp"
#include <map>


namespace FrameWork
{
    void DrawTexture(glm::vec2 pos, glm::vec2 sizeStart, glm::vec2 sizeEnd, glm::vec2 scale,GLfloat r,TextureFile data)
    {
        glColor3f(1.0f,1.0f,1.0f);

        float dx = 1.0f / (FrameWork::windowContext->getSize().x / 2);
        float dy = 1.0f / (FrameWork::windowContext->getSize().y / 2);
        pos = FrameWork::getWindowPosition(pos);

        GLuint texture;

        //UVのピクセル単位で算出
        glm::vec2 size;
        size.x = 1.0f / (float)data.size.x;
        size.y = 1.0f / (float)data.size.y;
 
        //表示域を算出
        glm::vec2 start = size * sizeStart;
        glm::vec2 end = size * sizeEnd;

        glGenTextures(1,&texture);
        glBindTexture(GL_TEXTURE_2D,texture);
        glEnable(GL_TEXTURE_2D);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.size.x, data.size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (byte*)data.fileData);

        // テクスチャの補間設定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glm::vec2 s = glm::abs(sizeEnd - sizeStart) * glm::vec2(dx,dy);

        glPushMatrix();
        {
            glMatrixMode(GL_MODELVIEW);
            glTranslatef(pos.x + (s.x / 2.0f), pos.y - (s.y / 2.0f), 0);
            
            
            glScalef(s.x / 2 + (scale.x * dx), s.y / 2  + (scale.y * dy), 0);
            glRotated(FrameWork::GetAngle(r), 0, 0, 1);



            glBegin(GL_QUAD_STRIP);
            {

                glTexCoord2f(start.x, start.y);
                glVertex2f(-1, 1);

                glTexCoord2f(end.x, start.y);
                glVertex2f(1, 1);

                glTexCoord2f(start.x, end.y);
                glVertex2f(-1, -1);

                glTexCoord2f(end.x, end.y);
                glVertex2f(1, -1);

            }
            glEnd();

            glFinish();
        }
        glPopMatrix();

        glDeleteTextures(1,&texture);
        //stbi_image_free(*data->fileData); //画像データをdelete
    }




    // ##################################### 矩形 描画 ##################################### 
    void DrawRectangle(glm::vec2 start, glm::vec2 end,GLdouble r, glm::vec4 color)
    {   
        color = FrameWork::GetGlColor(color);
        glColor4f(color.x,color.y,color.z,color.w);


        float dx = 1.0f / (FrameWork::windowContext->getSize().x / 2);
        float dy = 1.0f / (FrameWork::windowContext->getSize().y / 2);

        const float aspect = FrameWork::windowContext->getSize().x / FrameWork::windowContext->getSize().y;  //アスペクト比
        const glm::vec2 offset = glm::vec2(aspect, -1.0f);
        const float rate = 2.0f / FrameWork::windowContext->getSize().y;

        glm::vec2 posStart = getWindowPosition(start) * offset;   //描画座標

        start = (start * rate) + offset;
        end = (end * rate) + offset;
        glm::vec2 rectSize = glm::vec2(std::abs(end.x - start.x) / 2.0f, std::abs(end.y - start.y) / 2.0f);    //Rectの(縦横半分の)サイズ
        
        glPushMatrix(); 
        {
            glMatrixMode(GL_MODELVIEW);
            glScalef(1.0f / aspect, -1.0f, 1);
            glTranslatef(posStart.x + rectSize.x, posStart.y + rectSize.y, 0);
            glRotated(FrameWork::GetAngle(r), 0,  0, 1);

            {
                glRectf(-rectSize.x, -rectSize.y, rectSize.x, rectSize.y);  //描画
            }

            glFinish();
        }
        glPopMatrix();

        
        
        
    }

    // ##################################### 円 描画 ##################################### 
    void DrawCircle(glm::vec2 pos,unsigned short num,unsigned short width,GLdouble r, glm::vec4 color)
    {
        const float aspect = FrameWork::windowContext->getSize().x / FrameWork::windowContext->getSize().y;  //アスペクト比
        const glm::vec2 offset = glm::vec2(aspect, -1.0f);
        const float rate = 2.0f / FrameWork::windowContext->getSize().y;

        float dx = 1.0f / (FrameWork::windowContext->getSize().x / 2);
        float dy = 1.0f / (FrameWork::windowContext->getSize().y / 2);

        color = FrameWork::GetGlColor(color);
        glColor4f(color.x, color.y,color.z, color.w);


        glm::vec2 w;
        w.x = width * dy;
        w.y = width * dy;

        pos = getWindowPosition(pos);

        glPushMatrix();
        {
            glMatrixMode(GL_MODELVIEW);

            glTranslated(pos.x + (width * dx) , pos.y - (width * dy), 0);

            glScaled(1.0f / aspect, 1.0f, 0);

            glRotated(FrameWork::GetAngle(r), 0, 0, -1);


            glBegin(GL_TRIANGLE_FAN);
            {
                float f = (PI * 2.0f) / (float)num;
                float ff = 0;
                for (unsigned short i = 0; i < num; i++)
                {
                    float x = cos(ff) * w.x;
                    float y = sin(ff) * w.y;
                    glVertex2f(x, y);
                    ff += f;
                }
            }
            glEnd();

            glFinish();
        }
        glPopMatrix();
    }


    // ##################################### 点 描画 ##################################### 
    void DrawPoint(glm::vec2 pos,GLfloat size,glm::vec4 color)
    {
        color = FrameWork::GetGlColor(color);
        glColor4f(color.x,color.y,color.z, color.w);

        glPointSize(size);  //サイズ
        pos = getWindowPosition(pos);
        
        glBegin(GL_POINTS);
        {
            glVertex2f(pos.x, pos.y);
        }
        glEnd();

        glFinish();
    }

    // ##################################### 線 描画 ##################################### 
    void DrawLine(glm::vec2 start,glm::vec2 end, GLfloat width,float r, glm::vec4 color)
    {

        color = FrameWork::GetGlColor(color);
        glColor4f(color.x, color.y,color.z, color.w);


        start = getWindowPosition(start);
        end = getWindowPosition(end);
        glm::vec2 size = glm::abs(end - start) / 2.0f;

        //width の最大値と最小値を得る
        GLfloat lineWidthRange[2] = { 0.0f, 0.0f };
        glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);

        if (width > lineWidthRange[1])
        {
            std::cerr << "glLineWidth();の最大値を超えました。" << std::endl;
            width = lineWidthRange[1];
        }
        else if (width < lineWidthRange[0])
        {
            std::cerr << "glLineWidth();の最小値を超えました。" << std::endl;
            width = lineWidthRange[0];
        }
            



        float dx = 1.0f / (FrameWork::windowContext->getSize().x / 2);
        float dy = 1.0f / (FrameWork::windowContext->getSize().y / 2);

        glPushMatrix();
        {
            glMatrixMode(GL_MODELVIEW);
            glTranslated(start.x + size.x, start.y - size.y, 0);
            //std::cout << "FameWork::Line: " << r << std::endl;
            //std::cout << "FameWork::Line: " << FrameWork::GetAngle(r) << std::endl;

            glRotated(FrameWork::GetAngle(r), 0, 0, -1);
            glLineWidth(width);  //太さ

            glBegin(GL_LINES);
            {
                glVertex2f(-size.x, size.y);
                glVertex2f(size.x, -size.y);
            }
            glEnd();

            glFinish();
        }
        glPopMatrix();



    }

    // ##################################### 三角形 描画 ##################################### 
    void DrawTriangle(glm::vec2 pos, glm::vec2 size, GLdouble r,glm::vec4 color)
    {
        float dx = 1.0f / (FrameWork::windowContext->getSize().x / 2);
        float dy = 1.0f / (FrameWork::windowContext->getSize().y / 2);
        

        color = FrameWork::GetGlColor(color);
        glColor4f(color.x, color.y,color.z, color.w);

        pos = getWindowPosition(pos);
        size.x = size.x * dx;
        size.y = size.y * dy;

        
        glPushMatrix();
        {
            glTranslated(pos.x, pos.y, 0);
            glRotated(FrameWork::GetAngle(r), 0, 0, -1);

            glBegin(GL_TRIANGLES);
            {
                glVertex2f(0,size.y / 2);
                glVertex2f(-size.x / 2, -size.y / 2);
                glVertex2f(size.x / 2,  -size.y / 2);
            }
            glEnd();

            glFinish();
        }
        glPopMatrix();

    }

    // ##################################### 楕円 描画 ##################################### 
    void DrawEllipse(glm::vec2 pos,glm::vec2 size, unsigned short num,GLdouble r, glm::vec4 color)
    {
        float dx = 1.0f / (FrameWork::windowContext->getSize().x / 2);
        float dy = 1.0f / (FrameWork::windowContext->getSize().y / 2);
        const float aspect = FrameWork::windowContext->getSize().x / FrameWork::windowContext->getSize().y;  //アスペクト比
        const glm::vec2 offset = glm::vec2(aspect, -1.0f);
        const float rate = 2.0f / FrameWork::windowContext->getSize().y;

        color = FrameWork::GetGlColor(color);
        glColor4f(color.x,color.y,color.z, color.w);

       
        pos = getWindowPosition(pos);
         
        glPushMatrix();
        {
            glMatrixMode(GL_MODELVIEW);
            glScaled(1.0f / aspect, 1.0f, 0);
            glTranslated(pos.x + (size.x * dx), pos.y - (size.y * dy), 0);
            glRotated(FrameWork::GetAngle((float)r), 0, 0, -1);

            glBegin(GL_TRIANGLE_FAN);
            {
                float f = ((float)PI * 2.0f) / (float)num;
                float ff = 0;
                for (int i = 0; i < num; i++)
                {
                    float x = cos(ff) * size.x * dy;
                    float y = sin(ff) * size.y * dy;

                    glVertex2f(x, y);
                    ff += f;
                }
            }
            glEnd();

            glFinish();
        }
        glPopMatrix();

    }

    // ##################################### 簡易文字描画 ##################################### 
    void DrawText(const char *font,glm::vec2 pos, FT_UInt charSize, glm::vec4 color, const char* str, ...)
    {
        if (str != NULL)
        {
            FrameWork::Shader shader;

	        shader.Input(FrameWork::LoadShader("Shader/2D/BasicText_2D.vert")->data(),FrameWork::LoadShader("Shader/2D/BasicText_2D.frag")->data());
            GLuint vao; //vao
            GLuint vbo; //vbo

            struct Character
            {
                unsigned int textureID;  // グリフのテクスチャID
                glm::ivec2   Size;       // グリフサイズ
                glm::ivec2   Bearing;    // グリフのベースライン
                unsigned int Advance;    // 次のグリフまでのオフセット
            };

            //vao
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            //vbo
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            //頂点属性
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
            glEnableVertexAttribArray(0);

            //FreeTypeを初期化

            //FreeType
            FT_Library ft;  //freetype
            FT_Face face;   //フェイス

            //初期化 
            if (FT_Init_FreeType(&ft) != 0)
            {
                std::cerr << "ERROR: FREETYPE: Could not init FreeType Library" << std::endl;
            }

            //フェイス作成
            if (font != NULL) 
            {
                if (FT_New_Face(ft, font, 0, &face) != 0)
                {
                    std::cerr << "ERROR: FREETYPE: Failed to load font" << std::endl;
                }
            }
            else 
            {
                //フォントがNULLだったら既定のフォントをロードする
                if (FT_New_Face(ft, "abc", 0, &face) != 0)
                {
                    std::cerr << "ERROR: FREETYPE: Failed to load font" << std::endl;
                }

            }

            FT_Set_Pixel_Sizes(face, 0, charSize);  //ピクセルサイズを指定
            float scale = 1.0f;
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

            //アルファブレンドを有効
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            //色をRGBにして位置を反転
            pos.y = FrameWork::windowContext->getSize().y - pos.y - charSize;
            const float c = 1.0f / 255;
            color = FrameWork::GetGlColor(color);

            //マルチバイト文字をワイド文字変換
            wchar_t txt[1000] = { L'\0' };
            char text[1000];
            va_list args;
            va_start(args, str);
            vsprintf(text,str, args);
            va_end(args);

            int i, j, f;
            for (i = 0, j = 0; text[j]; i++, j += f)
            {
                f = (int)mbrtowc(txt + i, &text[j], (size_t)MB_CUR_MAX, nullptr);
            }

            //文字描画
            for (int i = 0; txt[i] != L'\0'; i++)
            {
                unsigned int texture = 0;

                //グリフをロード
                FT_Load_Glyph(face, FT_Get_Char_Index(face, txt[i]), FT_LOAD_RENDER);

                //文字データを設定
                Character ch =
                {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    (unsigned int)face->glyph->advance.x

                };

                //テクスチャを生成
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

                float xpos = pos.x + ch.Bearing.x * scale;
                float ypos = pos.y - (ch.Size.y - ch.Bearing.y) * scale;

                float w = ch.Size.x * scale;
                float h = ch.Size.y * scale;

                float vertices[6][4] =
                {
                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos,     ypos,       0.0f, 1.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },

                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },
                    { xpos + w, ypos + h,   1.0f, 0.0f }

                };

                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

                shader.setEnable(); //シェーダーを有効にする

                //Unform
                shader.setUniform4f("uTextColor", color);
                shader.setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::windowContext->getSize().x, 0.0f, FrameWork::windowContext->getSize().y));

                glDrawArrays(GL_TRIANGLES, 0, 6);

                glBindTexture(GL_TEXTURE_2D, 0);
                glDeleteTextures(1, &ch.textureID);
                shader.setDisable();            //シェーダーを無効にする

                pos.x += ((ch.Advance >> 6) * scale); //次のグリフに進める

            }

            //解放

            // vao vbo
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDeleteVertexArrays(1, &vao);
            glDeleteBuffers(1, &vbo);

            //グリフ解放
            FT_Done_Face(face);
            //FT_Done_FreeType(ft);
        }
    }




    // ##################################### スクリーン座標を取得 ##################################### 
    glm::vec2 getWindowPosition(glm::vec2 pos)
    {
        float dx = 1.0f / (FrameWork::windowContext->getSize().x / 2.0f);
        float dy = 1.0f / (FrameWork::windowContext->getSize().y / 2.0f);

        pos.x = ((pos.x * dx) - 1.0f);
        pos.y = (1.0f - (pos.y * dy));

        return pos;
    }


}


