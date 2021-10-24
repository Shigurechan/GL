#include "../header/FrameWork.hpp"
#include "../header/Resource.hpp"

#include <iostream>
#include "../header/Camera.hpp"


int main()
{
	FrameWork::Init(glm::ivec2(800, 600), glm::ivec2(4,2), "FrameWork");	//　初期化
	FrameWork::Camera::Init();	//カメラ初期化


	FrameWork::ObjFile cubeFile;
	FrameWork::D3::LoadObj("Model/Cube.obj",cubeFile);
	FrameWork::D3::Object cube(cubeFile);


	FrameWork::ObjFile groundFile;
	FrameWork::D3::LoadObj("Model/ground.obj",groundFile);
	FrameWork::D3::Object ground(groundFile);



	float y = 0;
	float x = 0;

	float angleY = 0;
	float angleX = 0;

	while (*FrameWork::windowContext)
	{
		FrameWork::windowContext->FrameUpdate(glm::vec4(0,0,0,255));



		if(FrameWork::windowContext->getKeyInput(GLFW_KEY_LEFT) > (short)0)
		{
			x += 0.1;
//			printf("left\n");
//			printf("%f , %f \n",x,y);

		}
		else if(FrameWork::windowContext->getKeyInput(GLFW_KEY_RIGHT) > (short)0) 
		{
			x += -0.1;
//			printf("right\n");
//			printf("%f , %f \n",x,y);

		}

		if(FrameWork::windowContext->getKeyInput(GLFW_KEY_UP) > (short)0)
		{
			y += 0.1;
//			printf("up\n");
//			printf("%f , %f \n",x,y);


		}
		else if(FrameWork::windowContext->getKeyInput(GLFW_KEY_DOWN) > (short)0) 
		{
			y += -0.1;
//			printf("down\n");
//			printf("%f , %f \n",x,y);

		}


		
		if(FrameWork::windowContext->getKeyInput(GLFW_KEY_A) > (short)0)
		{
			angleY = 0.001;
			
			cube.setRotate(glm::vec3(0,1,0),angleY);
		}
		else if(FrameWork::windowContext->getKeyInput(GLFW_KEY_D) > (short)0) 
		{
			angleY = -0.001;
			cube.setRotate(glm::vec3(0,1,0),angleY);

		}
		else if(FrameWork::windowContext->getKeyInput(GLFW_KEY_W) > (short)0)
		{
			angleY = 0.001;
			cube.setRotate(glm::vec3(1,0,0),angleY);

		}
		else if(FrameWork::windowContext->getKeyInput(GLFW_KEY_S) > (short)0) 
		{
			angleY = -0.001;
			cube.setRotate(glm::vec3(1,0,0),angleY); 
		}
		
		FrameWork::Camera::setLook(glm::vec3(x,y,-1));
		FrameWork::Camera::setPosition(glm::vec3(0,0,200.0f));


		//Cube
		cube.shader->setEnable();
		cube.setPosition(glm::vec3(0,10,0));
		cube.setScale(glm::vec3(30,30,30));
		cube.shader->setUniform3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		cube.shader->setUniform3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		cube.shader->setUniform3f("lightPos", glm::vec3(0,0,10.0f));
		printf("あああ\n");
		cube.shader->setUniform3f("viewPos",FrameWork::Camera::getPosition());
		printf("いいい\n");

		cube.Renderer();
		cube.shader->setDisable();

		//Ground
		ground.shader->setEnable();
		ground.setPosition(glm::vec3(0,-50,-5));
		ground.setScale(glm::vec3(20,20,20));
		ground.shader->setUniform3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		ground.shader->setUniform3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		ground.shader->setUniform3f("lightPos", glm::vec3(0,0,10));
//		ground.shader->setUniform3f("viewPos", FrameWork::Camera::getPosition());
		ground.Renderer();
		ground.shader->setDisable();






		FrameWork::windowContext->Wait();
		FrameWork::windowContext->SwapBuffers();
	}



	

	return 0;
}
