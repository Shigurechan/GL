#ifndef ___SIMPLE_HPP_
#define ___SIMPLE_HPP_

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Resource.hpp"

/*#########################################################################
# 簡易 描画関数
###########################################################################*/
namespace FrameWork
{
	namespace D2
	{
		void DrawText(const char* font,glm::vec2 pos, FT_UInt charSize, glm::vec4 color,  const char* str, ...);			//文字
		void DrawTexture(glm::vec2 pos, glm::vec2 sizeStart, glm::vec2 sizeEnd,glm::vec2 scale,GLfloat r,TextureFile data);	//テクスチャ描画
		void DrawRectangle(glm::vec2 start,glm::vec2 end,GLdouble r,glm::vec4 color);								//矩形
		void DrawCircle(glm::vec2 pos, unsigned short num, unsigned short width, GLdouble r, glm::vec4 color);			//円
		void DrawPoint(glm::vec2 pos, GLfloat size, glm::vec4 color);										//点
		void DrawLine(glm::vec2 start, glm::vec2 end, GLfloat width, float r, glm::vec4 color);						//線
		void DrawTriangle(glm::vec2 pos, glm::vec2 size, GLdouble r, glm::vec4 color);							//三角形
		void DrawEllipse(glm::vec2 pos,glm::vec2 size, unsigned short num, GLdouble r, glm::vec4 color);				//楕円
		glm::vec2 getWindowPosition(glm::vec2 pos);	//スクリーン座標を取得
	}
}
#endif
