#include "../header/FrameWork.hpp"

#include <iostream>
#include "../header/Camera.hpp"


int main()
{
	FrameWork::Init(glm::ivec2(48 * 26, 48 * 18), glm::ivec2(4,2), "FrameWork");	//　初期化
	FrameWork::Camera::Init();	//カメラ初期化


	float f = 0;
	while (*FrameWork::windowContext)
	{
		FrameWork::windowContext->FrameUpdate(glm::vec4(0,0,0,255));

		








		f += PI / 100.0f;


		FrameWork::windowContext->Wait();
		FrameWork::windowContext->SwapBuffers();
	}



	

	return 0;
}
