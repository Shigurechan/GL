#include "../header/Init.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../header/Window.hpp"
#include "../header/Resource.hpp"

namespace FrameWork
{
	std::shared_ptr<FrameWork::Window> windowContext = 0;

	// ##################################### 初期化 #####################################
	bool Init(glm::ivec2 size, glm::ivec2 ver, const char *title)
	{

		if (FT_Init_FreeType(&ft) != 0)
		{
			std::cerr << "FreeType を初期化出来ません。" << std::endl;
			assert(0);
		}

		setlocale(LC_CTYPE, ""); //ローカルを設定

		if (glfwInit() == GL_FALSE)
		{
			std::cerr << "glfw初期化失敗。" << std::endl;
			return false;
		}

		windowContext = std::make_shared<Window>(size, title); //ウインドウコンテキストを生成

		glEnable(GL_BLEND);						//ブレンド有効
		glEnable(GL_TEXTURE_2D);					//テクスチャを有効
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//ブレンドタイプ
		glEnable(GL_MULTISAMPLE);				   	//MSAA
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);			//半透明
		glEnable(GL_DEPTH_TEST);				   	//深度バッファを有効
		//glDepthFunc(GL_ALWAYS);					   	//深度バッファのタイプ
		//glDepthFunc(GL_LEQUAL);

		glEnable(GL_CULL_FACE);					   	//カリングを有効
		glCullFace(GL_BACK);					   	//裏面を無効

		//マウス移動
		if (GLFW_NOT_INITIALIZED == glfwRawMouseMotionSupported())
		{
			std::cerr << "GLFW_NOT_INITIALIZED" << std::endl;
		}

		// OpenGL Verison 4.5 Core Profile　を選択する
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ver.x);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ver.y);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		atexit(glfwTerminate); //プログラム終了時の処理を登録

		return true;
	}

}