#include "../header/Window.hpp"

#include <limits.h>
#include <chrono>
#include <thread>
#include <time.h>
#include <GLFW/glfw3.h>
#include <GL/glew.h>



// ##################################### コンストラクタ ##################################### 
FrameWork::Window::Window(glm::ivec2 size, const char* title)
{
	window = std::make_shared<GLFWwindow*>(glfwCreateWindow(size.x, size.y, title, NULL, NULL));
//	window = glfwCreateWindow(size.x, size.y, title, NULL, NULL);

	//変数を初期化
	std::fill(std::begin(keyBoard), std::end(keyBoard), 0);		//キーボード入力配列を初期化
	std::fill(std::begin(key), std::end(key), 0);				//キーボード入力配列を初期化
	std::fill(std::begin(mouseButton), std::end(mouseButton), 0);	//マウス入力配列を初期化

	mouseWheel = 0;	//マウスホイール
	inputKey = 0;	//文字入力

	//フレーム管理
	count = 0;		//現在のフレーム
	startCount = 0;	//最初の時間

	//コンテキストの作成に失敗
	if (*window == NULL)
	{
		std::cerr << "ウインドウ生成失敗" << std::endl;
		exit(1);	//異常終了
	}
	else 
	{
		//std::cout << "ウインドウコンテキスト初期化" << std::endl;
	}

	glfwMakeContextCurrent(*window);	//コンテキストを作成
	glfwSwapInterval(1);			//垂直同期

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLFW 初期化失敗" << std::endl;
		exit(1);
	}

	atexit(glfwTerminate);	//プログラム終了時の処理を登録
	glfwSwapInterval(1);	//垂直同期


	//イベント処理
	glfwSetWindowUserPointer(*window, this);	//このインスタンスのthis
	glfwSetWindowSizeCallback(*window, Resize);	//ウインドウサイズを変更する時に呼び出す処理
	glfwSetDropCallback(*window,DragAndDrop);	//ドラック＆ドロップ
	glfwSetScrollCallback(*window,MouseScroll);	//マウスのホイール
	glfwSetCharCallback(*window,KeyInputChar);	//テキスト入力
	glfwSetKeyCallback(*window,KeyInput);		//キー入力
	

    	glfwSetInputMode(*window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);


	Resize(*window, size.x, size.y);	//リサイズ
}

// ##################################### イベント処理　キー入力 ##################################### 
void FrameWork::Window::KeyInput(GLFWwindow* win, int key, int scanCode, int action, int mods)
{
	Window* const instance = (Window*)glfwGetWindowUserPointer(win);


	if (action == GLFW_PRESS)
	{
		instance->key[key] = TRUE;
	}
	else if (action == GLFW_RELEASE)
	{
		instance->key[key] = FALSE;
	}


}
// ##################################### イベント処理　画面サイズ変更 ##################################### 
void FrameWork::Window::Resize(GLFWwindow* const win, int width, int height)
{
	int fbWidth, fbHeight;
	glfwGetFramebufferSize(win, &fbWidth, &fbHeight);
	glViewport(0, 0, fbWidth, fbHeight);

	Window* const instance = (Window*)glfwGetWindowUserPointer(win);

	if (instance != NULL)
	{
		instance->size.x = (GLfloat)width;
		instance->size.y = (GLfloat)height;		
	}
}

// ##################################### イベント処理　マウススクロール ##################################### 
void FrameWork::Window::MouseScroll(GLFWwindow* win,double x, double y)
{
	Window* const instance = (Window*)glfwGetWindowUserPointer(win);

	if (instance != NULL)
	{
		if (y > 0)
		{
			if (instance->mouseWheel == SHRT_MAX)
			{
				instance->mouseWheel = SHRT_MAX - 1;
			}

			instance->mouseWheel += 1;
		}
		else if(y < 0)
		{
			if (instance->mouseWheel == SHRT_MIN)
			{
				instance->mouseWheel = -(SHRT_MIN + 1);
			}

			instance->mouseWheel += -1;
		}
	}	
}

// ##################################### マウススクロールを取得 ##################################### 
short int FrameWork::Window::getMouseScroll()
{
	return mouseWheel;
}

// ##################################### ドラック＆ドロップしたパスを取得 ##################################### 
const std::string FrameWork::Window::getDropPath()const
{
	return drop;
}

// ##################################### イベント処理　ドラック＆ドロップ ##################################### 
void FrameWork::Window::DragAndDrop(GLFWwindow* const win,int num, const char* str[])
{
	Window* const instance = (Window*)glfwGetWindowUserPointer(win);

	if (instance != NULL)
	{
		instance->drop = std::string(str[0]);		
	}
}

// ##################################### マウス座標を取得 ##################################### 
glm::ivec2 FrameWork::Window::getMousePos()
{
	double x;
	double y;
	glfwGetCursorPos(*window,&x,&y);

	glm::vec2 pos((int)x, (int)y);

	return pos;
}

// ##################################### マウスボタン入力 ##################################### 
int FrameWork::Window::getMouseButton(int mouse )
{
	if (glfwGetMouseButton(*window, mouse))
	{
		mouseButton[mouse]++;

		//値のオーバーフローを防ぐ
		if (mouseButton[mouse] > 6000)
		{
			mouseButton[mouse] = 6000;
		}
	}
	else
	{
		mouseButton[mouse] = 0;
	}

	return mouseButton[mouse];
}

// ##################################### ミリ秒を取得 ##################################### 
int FrameWork::Window::getNowTime()
{
	return (int)(glfwGetTime() * 1000.0f);
}

// ##################################### 待機フレームを計算 ##################################### 
void FrameWork::Window::FrameUpdate(glm::vec4 color)
{
	glClearDepth(1.0f);
	float c = 1.0f / 255.0f;
	glClearColor(color.x * c, color.y * c, color.z * c, color.w * c);							//カラーバッファのクリア色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);	//フレームバッファを初期化

	//フレームレートを制御する
	if (count == 0)
	{
		startCount = getNowTime();
	}

	if (count == FRAME_RATE)
	{
		startCount = getNowTime();
		count = 0;
	}
	
	//count++;
	count += 1;
}

// ##################################### フレームを取得 ##################################### 
int FrameWork::Window::getFrame()const
{
	return count;
}

// ##################################### フレームレート　待機 ##################################### 
void FrameWork::Window::Wait()
{
	int tookTime = getNowTime() - startCount;	
	int waitTime = count * 1000 / FRAME_RATE - tookTime;

	if (waitTime > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));

	}
}

// ##################################### ウインドウサイズを取得 ##################################### 
const glm::vec2 FrameWork::Window::getSize() const
{
	return size;
}

// ##################################### イベント処理　キー入力 ##################################### 
short int FrameWork::Window::getKeyInput(short int code)
{	
	if (key[code] == TRUE)
	{
		if (keyBoard[code] == SHRT_MAX)
		{
			keyBoard[code] = SHRT_MAX - 1;
		}
		keyBoard[code] += 1;
	}
	else 
	{
		keyBoard[code] = 0;
	}

	return keyBoard[code];
}

// ##################################### bool 演算子 ##################################### 
FrameWork::Window::operator bool()
{
	glfwPollEvents();	//イベントを取り出す

	
#ifndef DEBUG
	//エラー処理
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{

		std::cerr <<"\n"<< "	glGetError(): 0x" << std::hex << err << std::endl;
	}
#endif
	
	//ESCキーで終了
	if (glfwGetKey(*window, GLFW_KEY_ESCAPE) == 1)
	{
		exit(1);
	}

	//ウインドウを閉じる必要があれば false
	if (glfwWindowShouldClose(*window) != 0)
	{
		return false;
	}
	else 
	{
		return true;
	}

}

// ##################################### イベント処理　テキスト入力 ##################################### 
void FrameWork::Window::KeyInputChar(GLFWwindow* win, unsigned int n)
{
	Window* const instance = (Window*)glfwGetWindowUserPointer(win);

	instance->inputKey = (char)n;		
}

// ##################################### テキスト入力を取得 ##################################### 
std::vector<char> FrameWork::Window::getTextInput()
{	


	if (inputKey != 0)
	{
		if (string.size() == 0)
		{
			string.push_back(inputKey);
			string.push_back('\0');
		}
		else 
		{
			string.erase(string.end() - 1);
			string.push_back(inputKey);
			string.push_back('\0');
		}
	}

	short int key = getKeyInput(GLFW_KEY_BACKSPACE);
	if ( key == 1)
	{
		if (string.size() > 1) 
		{
			string.erase(string.end() - 2);
		}
	}
	else if (key > 30)
	{
		if (string.size() > 1)
		{
			string.erase(string.end() - 2);
		}
	}




	inputKey = 0;
	return string;
}

// ##################################### テキスト入力をクリア ##################################### 
void FrameWork::Window::ClearTextInput()
{
	//inputKey = 0;
}

// ##################################### ダブルバッファリング ##################################### 
void FrameWork::Window::SwapBuffers()const
{
	glfwSwapBuffers(*window);
}

// ##################################### デストラクタ ##################################### 
FrameWork::Window::~Window()
{
	glfwDestroyWindow(*window);
}