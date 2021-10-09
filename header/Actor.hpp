#ifndef ACTOR_HPP_
#define ACTOR_HPP_


namespace FrameWork
{
	namespace D2
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
}
#endif