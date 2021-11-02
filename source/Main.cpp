#include "../header/FrameWork.hpp"
#include "../header/Resource.hpp"

#include <iostream>
#include "../header/Camera.hpp"
#include "../header/VertexData.hpp"


int main()
{
	FrameWork::Init(glm::ivec2(800, 600), glm::ivec2(4, 2), "FrameWork"); //初期化
	FrameWork::Camera::Init();							    //カメラ初期化



//	FrameWork::Shader shaderCube("Shader/3D/BasicMono.vert","Shader/3D/BasicMono.frag");
	//FrameWork::Shader shaderCube("Shader/3D/BasicMaterial.vert","Shader/3D/BasicMaterial.frag");

//	FrameWork::Shader shaderCube("Shader/3D/BasicTexture.vert","Shader/3D/BasicTexture.frag");
//	FrameWork::Shader shaderCube("Shader/3D/BasicLightMap.vert","Shader/3D/BasicLightMap.frag");
//	FrameWork::Shader shaderCube("Shader/3D/Texture/DirectionalLight.vert","Shader/3D/Texture/DirectionalLight.frag");
//	FrameWork::Shader shaderCube("Shader/3D/Texture/PointLight.vert","Shader/3D/Texture/PointLight.frag");
	FrameWork::Shader shaderCube("Shader/3D/Texture/SpotLight.vert","Shader/3D/Texture/SpotLight.frag");

//	FrameWork::Shader shaderCube("Shader/3D/BasicPhong.vert","Shader/3D/BasicPhong.frag");
//	FrameWork::Shader shaderGround("Shader/3D/BasicMono.vert","Shader/3D/BasicMono.frag");
//	FrameWork::Shader shaderLightCube("Shader/3D/BasicMono.vert","Shader/3D/BasicMono.frag");

	//FrameWork::TextureFile texture = FrameWork::LoadTexture("Model/debug.png");
	//FrameWork::TextureFile texture = FrameWork::LoadTexture("Model/CubeTexture.png");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GLuint texture1 = FrameWork::LoadTexture("Model/CubeTexture.png");
	//GLuint texture2 = FrameWork::LoadTexture("Model/LightMap.png");

	FrameWork::ObjFile cubeFile;
	FrameWork::D3::LoadObj("Model/TextureCube.obj", cubeFile);	
	FrameWork::D3::Object cube(&cubeFile,GL_STATIC_DRAW);
	cube.shader = &shaderCube;
	cube.shader->setVertexAttributeSize(sizeof(FrameWork::D3::VertexAttribute));
	cube.setVertexAttribute("vertexPosition",3);
	cube.setVertexAttribute("vertexUV",2);	
	cube.setVertexAttribute("vertexNormal",3);
	cube.setVertexBuffer();

	cube.setTexture(texture1);
	//cube.setTexture(texture2);

//	cube.shader->setEnable();
	//cube.shader->setUniform1i("material.diffuse",0);
	//cube.shader->setUniform1i("material.specular",1);		
	
//	cube.shader->setDisable();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

	FrameWork::ObjFile lightFile;
	FrameWork::D3::LoadObj("Model/cube.obj", lightFile);	
	FrameWork::D3::Object lightCube(&lightFile,GL_STATIC_DRAW);

	lightCube.shader = &shaderLightCube;
	lightCube.shader->setVertexAttributeSize(sizeof(FrameWork::D3::VertexAttribute));
	lightCube.setVertexAttribute("vertexPosition",3);
	lightCube.setVertexAttribute(NULL,2);
	lightCube.setVertexAttribute(NULL,3);
	lightCube.setVertexBuffer();



	FrameWork::ObjFile groundFile;
	FrameWork::D3::LoadObj("Model/cube.obj", groundFile);	
	FrameWork::D3::Object ground(&groundFile,GL_STATIC_DRAW);
	ground.shader = &shaderGround;
	ground.shader->setVertexAttributeSize(sizeof(FrameWork::D3::VertexAttribute));
	ground.setVertexAttribute("vertexPosition",3);
	ground.setVertexAttribute(NULL,2);
	ground.setVertexAttribute(NULL,3);
	ground.setVertexBuffer();

*/





	float z = 0;
	float x = 0;


	float angleY = 0;
	float angleX = 0;
	float cameraLookSpeed = PI / 100;	//視点移動速度
	float cameraMoveSpeed = 10.0f;	//移動速度
	glm::vec3 cameraLook = glm::vec3(PI /2,PI,0);
	glm::ivec3 cameraPos = glm::ivec3(0, 0, 100);


	glm::vec3 cubePos = glm::vec3(0,0,-1);
	glm::vec3 lightPos = glm::vec3(0,50,-1);	
	glm::vec3 groundPos = glm::vec3(0,0,-100);

	bool switchShader = false;

	while (*FrameWork::windowContext)
	{
		FrameWork::windowContext->FrameUpdate(glm::vec4(0, 0, 0, 255));

		if (FrameWork::windowContext->getKeyInput(GLFW_KEY_A) > (short)0)
		{
			printf("%f\n",lightPos.y);
		//	angleY = (PI / 100);
			lightPos.y += -1;
			cube.setRotateMult(glm::vec3(0, 1, 0), angleY);
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_D) > (short)0)
		{
			angleY = -(PI / 100);
			cube.setRotateMult(glm::vec3(0, 1, 0), angleY);
			//ground.setRotate(glm::vec3(1, 0, 0), angleY);
//			printf("%f\n",angleY);

		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_W) > (short)0)
		{
			angleY = PI / 100;
			cube.setRotateMult(glm::vec3(1, 0, 0), angleY);
//			printf("%f\n",angleY);
			//ground.setRotate(glm::vec3(1, 0, 0), angleY);
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_S) > (short)0)
		{
			angleY = -PI / 100;
			cube.setRotateMult(glm::vec3(1, 0, 0), angleY);
		}
		else if (FrameWork::windowContext->getKeyInput(GLFW_KEY_Z) > (short)0)
		{
			//cubePos.z += -50;
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
				glm::vec3 vec = glm::vec3(0,-1,0);
				cameraPos += vec * cameraMoveSpeed;
				
			}			
		}






		//FrameWork::Camera::setLook(cameraLook);
		//FrameWork::Camera::setLook(glm::vec3(0,0,-1));
		FrameWork::Camera::setLook(glm::vec3(cos(cameraLook.x) * cos(cameraLook.y), sin(cameraLook.y), sin(cameraLook.x) * cos(cameraLook.y)));
		FrameWork::Camera::setPosition(cameraPos);

/*
		// LightCube
		lightCube.shader->setEnable();
		lightCube.setPosition(lightPos);
		lightCube.setScale(glm::vec3(10, 10, 10));
		lightCube.shader->setUniform4f("uFragment",FrameWork::GetGlColor(glm::vec4(255,255,255,255)));		
		lightCube.Renderer();
		lightCube.shader->setDisable(); 

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Cube
		cube.shader->setEnable();
		cube.setPosition(cubePos);
		cube.setScale(glm::vec3(25, 25, 25));

		cube.shader->setUniform3f("light.position", lightPos);
		cube.shader->setUniform3f("light.direction", glm::vec3(0,-1,0));
		cube.shader->setUniform3f("light.ambient", glm::vec3( 0.2f, 0.2f, 0.2f));
		cube.shader->setUniform3f("light.diffuse", glm::vec3( 0.5f, 0.5f, 0.5f));
		cube.shader->setUniform3f("light.specular", glm::vec3(100.0f, 100.0f, 100.0f));
		cube.shader->setUniform1f("light.constant", 0.1f);
		cube.shader->setUniform1f("light.linear", 0.009f);
		cube.shader->setUniform1f("light.quadratic", 0.0032f);
		cube.shader->setUniform1f("light.cutOff", glm::cos(glm::radians(12.5f)));
        	cube.shader->setUniform1f("light.outerCutOff", glm::cos(glm::radians(17.5f)));

		cube.shader->setUniform3f("material.specular", glm::vec3(1,1,1));
		cube.shader->setUniform1f("material.shininess", 64.0f);
		cube.shader->setUniform3f("uViewPosition", FrameWork::Camera::getPosition());
		
	

		/*

		cube.shader->setUniform3f("light.position", lightPos);
		cube.shader->setUniform3f("light.ambient", glm::vec3( 0.2f, 0.2f, 0.2f));
		cube.shader->setUniform3f("light.diffuse", glm::vec3( 0.5f, 0.5f, 0.5f));
		cube.shader->setUniform3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		cube.shader->setUniform1f("material.shininess", 64.0f);
		cube.shader->setUniform3f("uViewPosition", FrameWork::Camera::getPosition());
		
		*/
		cube.Renderer();
		cube.shader->setDisable();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		/*

		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGet。"light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		// material properties
		cube.shader->setUniform3f("material.ambient",glm::vec3(1.0f, 0.5f, 0.31f));
		cube.shader->setUniform3f("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
		cube.shader->setUniform3f("material.specular", glm::vec3( 0.5f, 0.5f, 0.5f)); // specular lighting doesn't have full effect on this object's material
		cube.shader->setUniform1f("material.shininess", 32.0f);
		cube.shader->setUniform3f("uViewPosition", FrameWork::Camera::getPosition());
		*/

		/*
		cube.shader->setUniform3f("uObjectColor", FrameWork::GetGlColor(glm::vec4(255,255,255,255)));
		cube.shader->setUniform3f("uLightColor", FrameWork::GetGlColor(glm::vec4(255,255,255,255)));
		cube.shader->setUniform3f("uLightPosition",lightPos);
		cube.shader->setUniform3f("uViewPosition", FrameWork::Camera::getPosition());
		cube.shader->setUniform1f("uAmbientStrength",0.1f);
		cube.shader->setUniform1f("uSpecularStrength",0.5f);
		cube.shader->setUniform1f("uShininessStrength",16.0f);
		*/


	//	cube.shader->setUniform4f("uFragment",FrameWork::GetGlColor(glm::vec4(100,0,0,255)));

/*

		// Ground
		ground.shader->setEnable();
		ground.setPosition(groundPos);
		ground.setScale(glm::vec3(1000, 1,1000));
		ground.shader->setUniform4f("uFragment",FrameWork::GetGlColor(glm::vec4(0,100,0,255)));
		ground.Renderer();
		ground.shader->setDisable();

*/










		FrameWork::D2::DrawText("Font/PressStart2P.ttf",glm::vec2(0,0),15,FrameWork::GetGlColor(glm::vec4(0,255,0,255)),"Position: %d,%d,%d",cameraPos.x,cameraPos.y,cameraPos.z);
		FrameWork::D2::DrawText("Font/PressStart2P.ttf",glm::vec2(0,15),15,FrameWork::GetGlColor(glm::vec4(0,255,0,255)),"Look: %.2f,%.2f,%.2f",cameraLook.x,cameraLook.y,cameraLook.z);







		FrameWork::windowContext->Wait();
		FrameWork::windowContext->SwapBuffers();
	}

	return 0;
}
