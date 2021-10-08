#include "../header/FrameWork.hpp"

#include <iostream>
#include "../header/FrameWork.hpp"
#include "../header/Sprite.hpp"
#include "../header/Camera.hpp"


int main()
{
	FrameWork::Init(glm::ivec2(48 * 26, 48 * 18), glm::ivec2(4,2), "FrameWork");	//　初期化
	FrameWork::Camera_2D::Init();	//カメラ初期化


	FrameWork::Circle cirlce;
	FrameWork::Point point;
	FrameWork::Rectangle rectangle;
	FrameWork::Line line;
	FrameWork::Triangle triangle;
	FrameWork::Ellipse ellipse;


	float f = 0;
	while (*FrameWork::windowContext)
	{
		FrameWork::windowContext->FrameUpdate(glm::vec4(0,0,0,255));


		//cirlce.Draw(glm::vec2(400,400),glm::ivec4(0,255,0,255),10,50,f);

		//point.Draw(glm::vec2(250,50),glm::ivec4(0,255,0,255),20);
		//rectangle.Draw(glm::vec2(350,50),glm::vec2(250,100),glm::ivec4(0,255,0,255),f);

		line.Draw(glm::vec2(450,50),glm::vec2(500,100),glm::vec4(0,255,0,255),20,f);//修正中

		//triangle.Draw(glm::vec2(600,50),glm::vec2(50,50),glm::ivec4(0,255,0,255),f);
		//ellipse.Draw(glm::vec2(700,50),glm::vec4(0,255,0,255),glm::vec2(50,20),50,f);











		f += PI / 100.0f;


		FrameWork::windowContext->Wait();
		FrameWork::windowContext->SwapBuffers();
	}



	

	return 0;
}
