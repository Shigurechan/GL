#ifndef ___TEXT_HPP_
#define ___TEXT_HPP_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdarg.h>
#include <map>

#include <glm/glm.hpp>

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
   namespace D2
   {
        class Text : public FrameWork::D2::Render
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
            }Character;

        public:

            Text();   //コンストラクタ
            ~Text();  //デストラクタ
        
            void setString(const byte ps,const glm::lowp_u8vec4 c,const char* args,...);
            void Draw(glm::vec2 pos);

        private:

            std::vector<wchar_t> getWchar_t(const char* str);
            void setTexture(const std::vector<wchar_t>& wc, std::vector<Character>& text);
            void RenderString(glm::vec2 pos);        

            std::vector<Character> text;
            glm::lowp_u8vec4 color; //色
            byte pixelSize;         //ピクセルサイズ
    
        };
        
    }
};
#endif