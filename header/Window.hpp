#ifndef ___WINDOW_HPP_
#define ___WINDOW_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include "Help.hpp"

/*#########################################################################
# Windowコンテキストクラス

説明
	ウインドウコンテキストとフレームレートとキー入力を制御
###########################################################################*/
namespace FrameWork
{
	class Window
	{

	public:

		Window(glm::ivec2 size = glm::ivec2(640,480), const char* title = "FrameWork");	//コンストラクタ
		~Window();													//デストラクタ

		operator bool();			//bool 演算子
		void SwapBuffers()const;	//ダブルバッファリング
		void ClearTextInput();		//テキスト入力をクリア


		//フレーム管理
		void FrameUpdate(glm::vec4 color);	//待機フレームを計算
		void Wait();				//待機
		int getFrame()const;			//フレームを取得
		int getNowTime();				//ミリ秒を取得

		const glm::vec2 getSize() const;			//サイズを取得
		const std::string getDropPath()const;		//ドラック＆ドロップしたパスを取得
		glm::ivec2 getMousePos();				//マウス座標を取得
		int getMouseButton(int mouse);			//マウスボタンが押されたかどうか？
		short int getMouseScroll();				//マウススクロールを取得
		short int getKeyInput(short int key);		//キー入力
		std::vector<char> getTextInput();			//テキスト入力	

		//イベント処理
		static void Resize(GLFWwindow* const win, int width, int height);				//画面サイズ変更
		static void DragAndDrop(GLFWwindow* const win, int num, const char* str[]);		//ドラック＆ドロップ
		static void MouseScroll(GLFWwindow* win,double x, double y);				//マウススクロール
		static void KeyInputChar(GLFWwindow* win, unsigned int n);					//テキスト入力
		static void KeyInput(GLFWwindow* win,int key,int scanCode,int action,int mods);	//キー入力


	private:

		std::vector<char> string;
		std::shared_ptr<GLFWwindow*> window;	//ウインドウコンテキスト

		glm::vec2 size;			//ウインドサイズ
		short int keyBoard[500];	//キー入力
		byte key[500];			//キー入力イベント処理
		int mouseButton[2];		//マウス入力
		short int mouseWheel;		//マウスホイール
		char inputKey;			//文字入力

		//フレーム管理
		int count;		//現在のフレーム
		int startCount;	//最初の時間


		std::string drop;	//ドラック＆ドロップしたパス
	};
}
#endif