#include "../header/FrameWork.hpp"

#include <iostream>
#include "../header/FrameWork.hpp"
#include "../header/Camera.hpp"


int main()
{
	FrameWork::Init(glm::ivec2(48 * 26, 48 * 18), glm::ivec2(4, 5), "Dungeon");	//　初期化
	FrameWork::Camera_2D::Init();	//カメラ初期化




	while (*FrameWork::windowContext)
	{
		FrameWork::windowContext->FrameUpdate(glm::vec4(0,0,0,255));


		


		FrameWork::windowContext->Wait();
		FrameWork::windowContext->SwapBuffers();
	}



	

	return 0;
}
