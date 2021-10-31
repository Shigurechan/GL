#include "../header/FrameWork.hpp"
#include "../header/Resource.hpp"

#include <iostream>
#include "../header/Camera.hpp"

int main()
{
	FrameWork::Init(glm::ivec2(800, 600), glm::ivec2(4, 2), "FrameWork"); //初期化
	FrameWork::Camera::Init();							    //カメラ初期化

	FrameWork::ObjFile lightFile;
	FrameWork::D3::LoadObj("Model/cube.obj", lightFile);
	//FrameWork::D3::Object lightCube(lightFile,"Shader/3D/BasicMono_3D.vert","Shader/3D/BasicMono_3D.frag");
	FrameWork::D3::Object lightCube(lightFile,"Shader/3D/Phong.vert","Shader/3D/Phong.frag");

	FrameWork::ObjFile cubeFile;
	FrameWork::D3::LoadObj("Model/cube.obj", cubeFile);
	FrameWork::D3::Object cube(cubeFile,"Shader/3D/Phong.vert","Shader/3D/Phong.frag");

	FrameWork::ObjFile groundFile;
	FrameWork::D3::LoadObj("Model/ground.obj", groundFile);
	FrameWork::D3::Object ground(groundFile,"Shader/3D/Phong.vert","Shader/3D/Phong.frag");

	float z = 0;
	float x = 0;

	float angleY = 0;
	float angleX = 0;

	float cameraLookSpeed = PI / 100;	//視点移動速度
	float cameraMoveSpeed = 10.0f;	//移動速度
	glm::vec3 cameraLook = glm::vec3(PI /2,PI,0);
	glm::ivec3 cameraPos = glm::ivec3(0, 130, 150);


	glm::vec3 cubePos = glm::vec3(0,0,-10);
	glm::vec3 lightPos = glm::vec3(0,200,0);
	glm::vec3 groundPos = glm::vec3(0,-1,-10);


	while (*FrameWork::windowContext)
	{
		FrameWork::windowContext->FrameUpdate(glm::vec4(0, 0, 0, 255));

		if (FrameWork::windowContext->getKeyInput(GLFW_KEY_A) > (short)0)
		{
			angleY = 0.001;

			cube.setRotate(glm::vec3(0, 1, 0), angleY);
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_D) > (short)0)
		{
			angleY += -(PI / 100);
			//cube.setRotate(glm::vec3(0, 1, 0), angleY);
			ground.setRotate(glm::vec3(1, 0, 0), angleY);
			printf("%f\n",angleY);

		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_W) > (short)0)
		{
			angleY += PI / 100;
			//cube.setRotate(glm::vec3(1, 0, 0), angleY);
			printf("%f\n",angleY);
			ground.setRotate(glm::vec3(1, 0, 0), angleY);
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


		//視線操作
		if (FrameWork::windowContext->getKeyInput(GLFW_KEY_LEFT_CONTROL) > 0)
		{			
			if (FrameWork::windowContext->getKeyInput(GLFW_KEY_LEFT) > (short)0)
			{
				cameraLook.x += -cameraLookSpeed;
			}
			else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_RIGHT) > (short)0)
			{
				cameraLook.x += cameraLookSpeed;
			}
			
			if (FrameWork::windowContext->getKeyInput(GLFW_KEY_UP) > (short)0)
			{
				cameraLook.y += -cameraLookSpeed;
			}
			else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_DOWN) > (short)0)
			{
				cameraLook.y += cameraLookSpeed;
			}			
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_LEFT_CONTROL) == 0)
		{
			if (FrameWork::windowContext->getKeyInput(GLFW_KEY_LEFT) > (short)0)
			{
				glm::vec3 vec = glm::vec3( sin(cameraLook.x) * cos(cameraLook.y), 0, cos(cameraLook.x) * cos(cameraLook.y) * -1);
				cameraPos += vec * cameraMoveSpeed;
			}
			else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_RIGHT) > (short)0)
			{
				glm::vec3 vec = glm::vec3( sin(cameraLook.x) * cos(cameraLook.y) * -1, 0, cos(cameraLook.x) * cos(cameraLook.y));
				cameraPos += vec * cameraMoveSpeed;				
			}
			
			if (FrameWork::windowContext->getKeyInput(GLFW_KEY_UP) > (short)0)
			{
				//glm::vec3 vec = glm::vec3( sin(cameraLook.x) * cos(cameraLook.y) * -1, sin(cameraLook.y), cos(cameraLook.x) * cos(cameraLook.y));
				glm::vec3 vec = glm::vec3(0,1,0);
				cameraPos += vec * cameraMoveSpeed;

				
			}
			else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_DOWN) > (short)0)
			{
				//glm::vec3 vec = glm::vec3( sin(cameraLook.x) * cos(cameraLook.y) * -1, sin(cameraLook.y), cos(cameraLook.x) * cos(cameraLook.y));
				glm::vec3 vec = glm::vec3(0,-1,0);
				cameraPos += vec * cameraMoveSpeed;
				
			}			
		}







		//FrameWork::Camera::setLook(cameraLook);
		//FrameWork::Camera::setLook(glm::vec3(0,0,-1));
		FrameWork::Camera::setLook(glm::vec3(cos(cameraLook.x) * cos(cameraLook.y), sin(cameraLook.y), sin(cameraLook.x) * cos(cameraLook.y)));
		FrameWork::Camera::setPosition(cameraPos);


		// LightCube
		lightCube.shader->setEnable();
		lightCube.setPosition(lightPos);
		lightCube.setScale(glm::vec3(1, 1, 1));
		//lightCube.shader->setUniform4f("uFragment",FrameWork::GetGlColor(glm::vec4(0,0,100,255)));		
		lightCube.shader->setUniform3f("objectColor", FrameWork::GetGlColor(glm::vec4(255,255,255,255)));
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
		//cube.Renderer();
		cube.shader->setDisable();

		// Ground
		ground.shader->setEnable();
		ground.setPosition(groundPos);
		ground.setRotate(glm::vec3(1,0,0),PI);
		ground.setScale(glm::vec3(50, 50, 50));
		ground.shader->setUniform3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		ground.shader->setUniform3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		ground.shader->setUniform3f("lightPos", lightPos);
		ground.shader->setUniform3f("viewPos", FrameWork::Camera::getPosition());
		// ground.shader->setUniform4f("uFragment",FrameWork::GetGlColor(glm::vec4(0,100,0,255)));
		ground.Renderer();
		ground.shader->setDisable();












		FrameWork::D2::DrawText("Font/PressStart2P.ttf",glm::vec2(0,0),15,FrameWork::GetGlColor(glm::vec4(0,255,0,255)),"Position: %d,%d,%d",cameraPos.x,cameraPos.y,cameraPos.z);
		FrameWork::D2::DrawText("Font/PressStart2P.ttf",glm::vec2(0,15),15,FrameWork::GetGlColor(glm::vec4(0,255,0,255)),"Look: %.2f,%.2f,%.2f",cameraLook.x,cameraLook.y,cameraLook.z);







		FrameWork::windowContext->Wait();
		FrameWork::windowContext->SwapBuffers();
	}

	return 0;
}
