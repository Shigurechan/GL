#ifndef ___INIT_HPP
#define ___INIT_HPP

#include <glm/glm.hpp>
#include <iostream>
#include "Window.hpp"

namespace FrameWork
{
	extern std::shared_ptr<FrameWork::Window> windowContext;	//ウインドウコンテキスト

	bool Init(glm::ivec2 size, glm::ivec2 ver, const char* title);	//初期化
}
#endif