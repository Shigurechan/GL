#include "../header/FrameWork.hpp"
#include "../header/Resource.hpp"

#include <iostream>
#include "../header/Camera.hpp"

int main()
{
	FrameWork::Init(glm::ivec2(800, 600), glm::ivec2(4, 2), "FrameWork"); //　初期化
	FrameWork::Camera::Init();							    //カメラ初期化


	FrameWork::ObjFile lightFile;
	FrameWork::D3::LoadObj("Model/Cube.obj", lightFile);
	//FrameWork::D3::Object lightCube(lightFile,"Shader/3D/BasicMono_3D.vert","Shader/3D/BasicMono_3D.frag");
	FrameWork::D3::Object lightCube(lightFile,"Shader/3D/Phong.vert","Shader/3D/Phong.frag");

	FrameWork::ObjFile cubeFile;
	FrameWork::D3::LoadObj("Model/Cube.obj", cubeFile);
	FrameWork::D3::Object cube(cubeFile,"Shader/3D/Phong.vert","Shader/3D/Phong.frag");

	FrameWork::ObjFile groundFile;
	FrameWork::D3::LoadObj("Model/ground.obj", groundFile);
	FrameWork::D3::Object ground(groundFile,"Shader/3D/Phong.vert","Shader/3D/Phong.frag");

	float z = 0;
	float x = 0;

	float angleY = 0;
	float angleX = 0;

	float vecSpeed = PI / 1000;
	float moveSpeed = 5;

	glm::ivec2 prevPos = FrameWork::windowContext->getMousePos();
	glm::ivec2 nowPos;

	glm::vec3 cameraPos = glm::vec3(0, 0, 150);


	glm::vec3 cubePos = glm::vec3(0,0,0);

	glm::vec3 lightPos = glm::vec3(0,200,0);


	while (*FrameWork::windowContext)
	{
		FrameWork::windowContext->FrameUpdate(glm::vec4(0, 0, 0, 255));



		nowPos = FrameWork::windowContext->getMousePos();
		glm::vec2 vec = nowPos - prevPos;
		vec.x = vec.x * vecSpeed;
		vec.y = -vec.y * vecSpeed;

		glm::vec3 moveVec = glm::vec3(cos(vec.x) * cos(vec.y), sin(vec.y), sin(vec.x) * cos(vec.y)); //カメラ向き

		if (FrameWork::windowContext->getKeyInput(GLFW_KEY_A) > (short)0)
		{
			angleY = 0.001;

			cube.setRotate(glm::vec3(0, 1, 0), angleY);
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_D) > (short)0)
		{
			angleY = -0.001;
			cube.setRotate(glm::vec3(0, 1, 0), angleY);
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_W) > (short)0)
		{
			angleY = 0.001;
			cube.setRotate(glm::vec3(1, 0, 0), angleY);
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_S) > (short)0)
		{
			angleY = -0.001;
			cube.setRotate(glm::vec3(1, 0, 0), angleY);
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_Z) > (short)0)
		{
			cubePos.z += -50;
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_X) > (short)0)
		{
			cubePos.z += 50;
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_N) > (short)0)
		{
			lightPos.z += -20;
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_M) > (short)0)
		{
			lightPos.z += 20;
		}




		//カメラ移動
		if (FrameWork::windowContext->getKeyInput(GLFW_KEY_LEFT) > (short)0)
		{
			x += -moveSpeed;

			cameraPos.x += moveVec.x * 10;
			//cameraPos.z += moveVec.z * 10;

			//			printf("left\n");
			//			printf("%f , %f \n",x,y);
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_RIGHT) > (short)0)
		{
			x += moveSpeed;
			//			printf("right\n");
			//			printf("%f , %f \n",x,y);

			cameraPos.x += moveVec.x * 10;
			//cameraPos.z += moveVec.z * 10;
		}

		if (FrameWork::windowContext->getKeyInput(GLFW_KEY_UP) > (short)0)
		{
			z += moveSpeed;
			//			printf("up\n");
			//			printf("%f , %f \n",x,y);

			cameraPos.x += moveVec.x * 10;
			cameraPos.z += moveVec.z * 10;
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_DOWN) > (short)0)
		{
			z += -moveSpeed;
			//			printf("down\n");
			//			printf("%f , %f \n",x,y);

			cameraPos.x += moveVec.x * 10;
			cameraPos.z += moveVec.z * 10;
		}
		else
		{

		}

		FrameWork::Camera::setLook(glm::vec3(cos(vec.x) * cos(vec.y), sin(vec.y), sin(vec.x) * cos(vec.y)));
		FrameWork::Camera::setPosition(cameraPos);


		// LightCube
		lightCube.shader->setEnable();
		lightCube.setPosition(lightPos);
		lightCube.setScale(glm::vec3(1, 1, 1));
		//lightCube.shader->setUniform4f("uFragment",FrameWork::GetGlColor(glm::vec4(0,0,100,255)));		
		lightCube.shader->setUniform3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		lightCube.shader->setUniform3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		lightCube.shader->setUniform3f("lightPos",lightPos);
		lightCube.shader->setUniform3f("viewPos", FrameWork::Camera::getPosition());
		lightCube.Renderer();
		lightCube.shader->setDisable();

		// Cube
		cube.shader->setEnable();
		cube.setPosition(cubePos);
		cube.setScale(glm::vec3(50, 50, 50));
//		cube.shader->setUniform4f("uFragment",FrameWork::GetGlColor(glm::vec4(0,0,100,255)));
		cube.shader->setUniform3f("objectColor", FrameWork::GetGlColor(glm::vec4(255,255,255,255)));
		cube.shader->setUniform3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		cube.shader->setUniform3f("lightPos",lightPos);
		cube.shader->setUniform3f("viewPos", FrameWork::Camera::getPosition());
		cube.Renderer();
		cube.shader->setDisable();

		// Ground
		ground.shader->setEnable();
		ground.setPosition(glm::vec3(0, 0, 0));
		ground.setScale(glm::vec3(1, 1, 1));
		ground.shader->setUniform3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		ground.shader->setUniform3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		ground.shader->setUniform3f("lightPos", lightPos);
		ground.shader->setUniform3f("viewPos", FrameWork::Camera::getPosition());
		// ground.shader->setUniform4f("uFragment",FrameWork::GetGlColor(glm::vec4(0,100,0,255)));
//		ground.Renderer();
		ground.shader->setDisable();

		FrameWork::windowContext->Wait();
		FrameWork::windowContext->SwapBuffers();
	}

	return 0;
}
