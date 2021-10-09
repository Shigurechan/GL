#ifndef ___SHAPE_HPP_
#define ___SHAPE_HPP_

#include <glm/glm.hpp>
#include "Render.hpp"

namespace FrameWork
{

	namespace D2
	{
	      class Window;

		/*#########################################################################
		# 　楕円	
		###########################################################################*/
		class Ellipse : public FrameWork::D2::Render
		{

		public:

			Ellipse();		//コンストラクタ
			~Ellipse();		//デストラクタ

			void Draw(glm::vec2 pos,glm::vec4 color, glm::vec2 s, int num, float r);	// 描画		
			

		private:
			unsigned short vertNum;	//頂点数
			
		};

		/*#########################################################################
		# 線
		###########################################################################*/
		class Line : public FrameWork::D2::Render
		{

		public:

			Line();	//コンストラクタ
			~Line();	//デストラクタ

			void Draw(glm::vec2 start, glm::vec2 end, glm::vec4 color,unsigned short width, float r);	// 描画		

		private:

			float rotate = 0;

		};

		/*#########################################################################
		# 三角形
		###########################################################################*/
		class Triangle : public FrameWork::D2::Render
		{

		public:
			
			Triangle();		//コンストラクタ
			~Triangle();	//デストラクタ

			void Draw(const glm::vec2 pos,const glm::vec2 size,const glm::ivec4 color,GLfloat r);	// 描画		


		private:

			glm::vec2 size;
		};


		/*#########################################################################
		# 矩形
		###########################################################################*/
		class Rectangle : public FrameWork::D2::Render
		{

		public:

			Rectangle();	//コンストラクタ
			~Rectangle();	//デストラクタ

			void Draw(glm::vec2 start, glm::vec2 end, glm::vec4 color,float r);


		private:

		};

		/*#########################################################################
		# 点
		###########################################################################*/
		class Point : public FrameWork::D2::Render
		{

		public:

			Point();	//コンストラクタ
			~Point();	//デストラクタ

			void Draw(glm::vec2 p,glm::vec4 color,unsigned short s);	// 描画		

		private:

		};

		/*#########################################################################
		# 円
		###########################################################################*/
		class Circle : public FrameWork::D2::Render
		{

		public:

			Circle();	//コンストラクタ
			~Circle();	//デストラクタ

			void Draw(const glm::vec2 pos, const glm::vec4 color,const GLushort num,const GLushort width, const GLfloat r);	//描画

		private:

			unsigned short vertNum;
		};
		
	}
}
#endif