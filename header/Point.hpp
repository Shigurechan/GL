#ifndef ___Point_HPP_
#define ___Point_HPP_

#include <iostream>
#include <glm/glm.hpp>
#include "Render.hpp"

#include "Shader.hpp"
/*#########################################################################
# ライン描画クラス
###########################################################################*/
namespace FrameWork
{
	class Window;

	class Point : public FrameWork::Render_2D
	{

	public:

		Point();	//コンストラクタ
		~Point();	//デストラクタ

		void Draw(glm::vec2 p,glm::vec4 color,unsigned short s);	// 描画		

	private:

	};
}
#endif
