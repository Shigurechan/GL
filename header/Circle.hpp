#ifndef ___CIRCLE_HPP_
#define ___CIRCLE_HPP_
#include <iostream>
#include <vector>

#include "Shader.hpp"
#include "Render.hpp"
#include "VertexData.hpp"

/*#########################################################################
# 　円描画クラス

説明
	
###########################################################################*/

namespace FrameWork
{

	class Circle : public FrameWork::Render_2D
	{

	public:

		Circle();	//コンストラクタ
		~Circle();	//デストラクタ

		void Draw(const glm::vec2 pos, const GLushort num,const GLushort width, const GLfloat r);	//描画

	private:

		unsigned short vertNum;
	};

}
#endif


