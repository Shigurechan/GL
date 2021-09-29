#include "../header/Help.hpp"

#include <locale.h>
#include <stdio.h>
#include <random>
#include <iostream>
#include "../header/Window.hpp"
#include "../header/Init.hpp"

namespace FrameWork
{
    // ##################################### 乱数を取得 ##################################### 
	int GetRandom(int start, int end)
	{
		std::random_device rnd;                             // 非決定的な乱数生成器を生成
		std::mt19937 mt(rnd());                             //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> Rand(start, end);   // [start, end] 範囲の一様乱数	

		return Rand(mt);
	}

	// ##################################### ラジアンから度数を取得 ##################################### 
	float GetAngle(float r)
	{
		return 360 / (PI * 2) * r;
	}


	// #####################################　ウインドウの中心座標を取得 ##################################### 
	glm::vec2 GetWindowCenter()
	{
		return FrameWork::windowContext->getSize() / 2.0f;
	}


	// #####################################　openglの色を取得 ##################################### 
	glm::vec4 GetGlColor(const glm::vec4 rgb)
	{
		float c = 1.0f / 255.0f;
		return glm::vec4(rgb.x * c,rgb.y * c,rgb.z * c,rgb.w);
	}

}