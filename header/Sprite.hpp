#ifndef ___SPRITE_2D_HPP_
#define ___SPRITE_2D_HPP_

#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Render.hpp"
#include "VertexData.hpp"
#include "Resource.hpp"

/*#########################################################################
# スプライトクラス
説明
	2Dのテクスチャ描画　正射形
###########################################################################*/

/*#########################################################################
*NOTE 
* 
* 頂点の順番
* 0	      2,3
* 1,4		5
###########################################################################*/

namespace FrameWork
{
	class Window;

	//頂点配列を指定

	class Sprite : public FrameWork::Render_2D
	{

	public:

		Sprite();	//コンストラクタ
		~Sprite();	//デストラクタ

		void InputTexture(FrameWork::TextureFile tex);  //テクスチャ 設定
		
		void Draw(glm::vec2 pos, int texNum, float r, glm::vec2 s, glm::vec2 start, glm::vec2 end);	//　描画　設定

	private:
            void setAttribute();	//頂点情報　設定

		
		//テクスチャ範囲
		glm::vec2 startSize;	//始点
		glm::vec2 endSize;	//終点
		glm::ivec2 size;		//サイズ

		GLuint textureID;	//テクスチャID
		
	};
}
#endif