#ifndef ___TRIANGLE_HPP_
#define ___TRIANGLE_HPP_

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

	class Triangle : public FrameWork::Render_2D
	{

	public:
		
		Triangle();		//コンストラクタ
		~Triangle();	//デストラクタ

		void Draw(const glm::vec2 pos,const glm::vec2 size,const glm::ivec4 color,GLfloat r);	// 描画		


	private:

		glm::vec2 size;
	};
}
#endif
