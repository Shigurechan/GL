#include "../header/FrameWork.hpp"

#include <iostream>
#include "../header/FrameWork.hpp"
#include "../header/Camera.hpp"


int main()
{
	FrameWork::Init(glm::ivec2(48 * 26, 48 * 18), glm::ivec2(4, 2), "Dungeon");	//　初期化
	FrameWork::Camera_2D::Init();	//カメラ初期化

	FrameWork::Circle circle;
	FrameWork::Text text;
	text.setString(30,glm::vec4(255,0,0,255),"test %d",1);

	while (*FrameWork::windowContext)
	{
		FrameWork::windowContext->FrameUpdate(glm::vec4(0,0,0,255));

		//circle.Draw(glm::vec2(100,100),glm::vec4(0,255,0,255),100,100,20);
		text.DrawString(glm::vec2(100,100));




		FrameWork::windowContext->Wait();
		FrameWork::windowContext->SwapBuffers();
	}



	

	return 0;
}
