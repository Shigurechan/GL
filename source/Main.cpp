#include "../header/FrameWork.hpp"
#include "../header/Resource.hpp"

#include <iostream>
#include "../header/Camera.hpp"


int main()
{
	FrameWork::Init(glm::ivec2(800, 600), glm::ivec2(4,2), "FrameWork");	//　初期化
	FrameWork::Camera::Init();	//カメラ初期化

	FrameWork::ObjFile file;
	FrameWork::D3::LoadObj("Model/test.obj",file);
	FrameWork::D3::Object object(file);

	float y = 0;
	float x = 0;

	float angleY = 0;
	float angleX = 0;

	while (*FrameWork::windowContext)
	{
		FrameWork::windowContext->FrameUpdate(glm::vec4(0,0,0,255));



		if(FrameWork::windowContext->getKeyInput(GLFW_KEY_LEFT) > (short)0)
		{
			x += 0.001;
//			printf("left\n");
//			printf("%f , %f \n",x,y);

		}
		else if(FrameWork::windowContext->getKeyInput(GLFW_KEY_RIGHT) > (short)0) 
		{
			x += -0.001;
//			printf("right\n");
//			printf("%f , %f \n",x,y);

		}

		if(FrameWork::windowContext->getKeyInput(GLFW_KEY_UP) > (short)0)
		{
			y += 0.001;
//			printf("up\n");
//			printf("%f , %f \n",x,y);


		}
		else if(FrameWork::windowContext->getKeyInput(GLFW_KEY_DOWN) > (short)0) 
		{
			y += -0.001;
//			printf("down\n");
//			printf("%f , %f \n",x,y);

		}


		
		if(FrameWork::windowContext->getKeyInput(GLFW_KEY_A) > (short)0)
		{
			angleY = 0.001;
			
			object.setRotate(glm::vec3(0,1,0),angleY);
		}
		else if(FrameWork::windowContext->getKeyInput(GLFW_KEY_D) > (short)0) 
		{
			angleY = -0.001;
			object.setRotate(glm::vec3(0,1,0),angleY);

		}
		else if(FrameWork::windowContext->getKeyInput(GLFW_KEY_W) > (short)0)
		{
			angleY = 0.001;
			object.setRotate(glm::vec3(1,0,0),angleY);

		}
		else if(FrameWork::windowContext->getKeyInput(GLFW_KEY_S) > (short)0) 
		{
			angleY = -0.001;
			object.setRotate(glm::vec3(1,0,0),angleY); 
		}
		




		


		FrameWork::Camera::setLook(glm::vec3(x,y,-1));
		FrameWork::Camera::setPosition(glm::vec3(0,0,200));

		object.Renderer();





		FrameWork::windowContext->Wait();
		FrameWork::windowContext->SwapBuffers();
	}



	

	return 0;
}
