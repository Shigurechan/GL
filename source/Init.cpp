#include "../header/Init.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../header/Window.hpp"

namespace FrameWork
{
	std::shared_ptr<FrameWork::Window> windowContext = 0;

	// ##################################### 初期化 ##################################### 
	bool Init(glm::ivec2 size,glm::ivec2 ver, const char* title)
	{
		setlocale(LC_CTYPE, "");    //ローカルを設定

		if (glfwInit() == GL_FALSE)
		{
			std::cerr << "glfw初期化失敗。" << std::endl;
			return false;
		}

		windowContext = std::make_shared<Window>(size, title);	//ウインドウコンテキストを生成

		//OpenGL Verison 4.5 Core Profile　を選択する
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ver.x);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ver.y);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		atexit(glfwTerminate);	//プログラム終了時の処理を登録

		return true;
	}

}