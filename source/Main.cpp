#include "../header/FrameWork.hpp"

#include <iostream>
#include "../header/FrameWork.hpp"
#include "../header/Sprite.hpp"
#include "../header/Camera.hpp"


int main()
{
	FrameWork::Init(glm::ivec2(48 * 26, 48 * 18), glm::ivec2(4,0), "Dungeon");	//　初期化
	FrameWork::Camera_2D::Init();	//カメラ初期化

	//FrameWork::Circle circle;
	//FrameWork::Text text;
	//text.setString(30,glm::vec4(255,0,0,255),"Hello World");

	FrameWork::Sprite sprite;
	FrameWork::TextureFile file = FrameWork::LoadTexture("Assets/texture_1.png");
	sprite.InputTexture(file);

	while (*FrameWork::windowContext)
	{
		FrameWork::windowContext->FrameUpdate(glm::vec4(0,0,0,255));

//		text.DrawString(glm::vec2(100,100));
		sprite.Draw(glm::vec2(100,100),0,0,glm::vec2(1,1),glm::vec2(0,0),glm::vec2(100,100));





		FrameWork::windowContext->Wait();
		FrameWork::windowContext->SwapBuffers();
	}



	

	return 0;
}
