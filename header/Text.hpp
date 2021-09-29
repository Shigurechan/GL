#ifndef ___TEXT_HPP_
#define ___TEXT_HPP_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdarg.h>
#include <map>

#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Help.hpp"
#include "Render.hpp"
#include "VertexData.hpp"

/*#########################################################################
# 文字描画クラス

説明
    文字を描画する
###########################################################################*/


namespace FrameWork
{

    class Text : public FrameWork::Render_2D
    {
    private:

        //文字 構造体
        typedef struct 
        {
            GLuint textureID;           // グリフのテクスチャID
            glm::lowp_u8vec2   size;    // グリフサイズ
            glm::lowp_u8vec2   bearing; // グリフのベースライン
            unsigned short advance;     // 次のグリフまでのオフセット
            wchar_t character;          // 文字
            glm::lowp_u8vec4 color;     // 描画色
            byte pixelSize;             // ピクセルサイズ

        }Character;

        //文字列 構造体
        typedef struct 
        {
            std::shared_ptr<std::vector<Character>> text;   // 文字列
            glm::lowp_u16vec2 size;                         // 文字列のサイズ
            byte font;                                      // フォント
        }String;

    public:

        Text();   //コンストラクタ
        ~Text();  //デストラクタ

        // ##################################### 固定長文字列　文字列　設定 ##################################### 
      
        void setString( const byte pixelSize, const glm::lowp_u8vec4 color, const char* args,...)
        {
            
            //std::string str = std::format(text, args...);
            char buf[1024] = { '\0' };

            va_list va;
            va_start(va,args);
            vsprintf(buf,args,va);
            va_end(va);

            
            String string;
            string.text = std::make_shared<std::vector<Character>>(0);

            std::vector<wchar_t> wc = getWchar_t(buf);  //wchar_t型　取得
            setTexture(wc,string.text,color,pixelSize);    //テクスチャ　設定


            fixedLength->push_back(string);
        }

        void DrawString(glm::vec2 pos,byte n);

        void DrawSentence(glm::vec2 pos, unsigned short num, byte style);
    private:

        std::vector<wchar_t> getWchar_t(const char* str);
        void setTexture(const std::vector<wchar_t>& wc, std::shared_ptr<std::vector<Character>>& text, const glm::lowp_u8vec4 color, const byte pixelSize);
        void RenderString(glm::vec2 pos, const std::shared_ptr<std::vector<Character>> character);
        std::unique_ptr<std::vector<String>> fixedLength;    //　固定長文字列
        
    };
};
#endif