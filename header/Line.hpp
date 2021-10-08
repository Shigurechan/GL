#ifndef ___Line_HPP_
#define ___Line_HPP_
#include <iostream>
#include <glm/glm.hpp>
#include "Render.hpp"

#include "Shader.hpp"

/*#########################################################################
# ライン描画クラス
###########################################################################*/
namespace FrameWork
{
	class Line : public FrameWork::Render_2D
	{

	public:

		Line();	//コンストラクタ
		~Line();	//デストラクタ

		void Draw(glm::vec2 start, glm::vec2 end, glm::vec4 color,unsigned short width, float r);	// 描画		

	private:

		float rotate = 0;

	};
}
#endif