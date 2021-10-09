#ifndef ___HELP_HPP_
#define ___HELP_HPP_
#include <iostream>
#include <glm/glm.hpp>

/*#########################################################################
# 補助系の関数

説明

###########################################################################*/

namespace FrameWork
{

	#define PI ( (float)3.14159265359 )				//PI
	#define byte unsigned char					//バイト型
	#define FRAME_RATE ( (int)60 )				//フレームレート
	#define TRUE 0x01							//true
	#define FALSE 0x00						//false
	#define RGBA_COLOR ((float)( 1.0 / 255.0 ))		//RGB変換
	#define RADIAN ( 360.0 / (PI * 2.0 ) )			//ラジアンを度数

	int GetRandom(int start, int end);			//乱数を取得
	float GetAngle(float r);				//ラジアンから度数を取得
	glm::vec4 GetGlColor(const glm::vec4 rgb);	//0~1までの値を取得
	glm::vec2 GetWindowCenter();				//ウインドウの中心座標を取得
	
}
#endif
