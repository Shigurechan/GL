#ifndef ACTOR_HPP_
#define ACTOR_HPP_

#include <iostream>
#include "Render.hpp"
#include "VertexData.hpp"

namespace FrameWork
{
	class Actor
	{
	public:
		Actor()
		{

		}
		
		virtual void Update() = 0;		//更新
		virtual void Draw()const = 0;		//描画
	};
}
#endif