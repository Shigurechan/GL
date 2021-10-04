#ifndef ___ELLIPSE_HPP_
#define ___ELLIPSE_HPP_

#include <iostream>
#include <glm/glm.hpp>
#include "Render.hpp"

#include "Shader.hpp"
#include "Help.hpp"

/*#########################################################################
# ライン描画クラス
###########################################################################*/
namespace FrameWork
{
	class Window;

	class Ellipse : public FrameWork::Render_2D
	{

	public:

		Ellipse();		//コンストラクタ
		~Ellipse();		//デストラクタ

		void Draw(glm::vec2 pos,glm::vec4 color, glm::vec2 s, int num, float r);	// 描画		
		

	private:
		unsigned short vertNum;	//頂点数
	
	};
}
#endif