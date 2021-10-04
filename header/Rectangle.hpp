#ifndef ___RECTANGLE_HPP_
#define ___RECTANGLE_HPP_
#include <iostream>
#include <glm/glm.hpp>
#include "Render.hpp"

#include "Shader.hpp"


/*#########################################################################
# 矩形描画クラス
###########################################################################*/
namespace FrameWork
{
	class Rectangle : public FrameWork::Render_2D
	{

	public:

		Rectangle();	//コンストラクタ
		~Rectangle();	//デストラクタ

		void Draw(glm::vec2 start, glm::vec2 end, glm::vec4 color,float r);


	private:

	};
}
#endif

