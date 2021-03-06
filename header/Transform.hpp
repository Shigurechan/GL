#ifndef TRANSFORM_2D_HPP_
#define TRANSFORM_2D_HPP_

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>




namespace FrameWork
{
	namespace D2
	{
		class Transform
		{

		public:

			Transform();		//コンストラクタ
			~Transform();		//デストラクタ

			//設定
			void setPosition(glm::vec2 p);	//座標
			void setScale(glm::vec2 s);		//スケール
			void setRotate(float r);		//回転
			
			//取得
			glm::vec2 getPosition();	//座標
			glm::vec2 getScale();		//スケール
			float getRotate();		//回転

			//行列　取得
			glm::mat4 getMatTranslation();	//座標
			glm::mat4 getMatScale();		//スケール
			glm::mat4 getMatRotate();		//回転

		private:

			glm::vec2 position;	//座標
			glm::vec2 scale;		//拡大縮小
			float rotate;		//回転

			//行列
			glm::mat4 matScale;		//拡大縮小
			glm::mat4 matRotate;		//回転
			glm::mat4 matTranslation;	//平行移動

		};
	}

	
	namespace D3
	{
		class Transform
		{

		public:

			Transform();		//コンストラクタ
			~Transform();		//デストラクタ

			//設定
			void setPosition(glm::vec3 p);			//座標
			void setScale(glm::vec3 s);				//スケール
			void setRotate(glm::vec3 vec,float r);		//回転
			void setRotateMult(glm::vec3 vec,float r);	//回転 かけ算

			//取得
			glm::vec3 getPosition();	//座標
			glm::vec3 getScale();		//スケール
			glm::vec3 getRotateVector();	//回転方向
			float getRotateAngle();		//回転ラジアン

			//行列　取得
			glm::mat4 getMatTranslation();	//座標
			glm::mat4 getMatScale();		//スケール
			glm::mat4 getMatRotate();		//回転

		private:

			glm::vec3 position;	//座標
			glm::vec3 scale;		//拡大縮小
			glm::vec3 rotateVector;	//回転
			float rotateAngle;	//ラジアン

			//行列
			glm::mat4 matScale;		//拡大縮小
			glm::mat4 matRotate;		//回転
			glm::mat4 matTranslation;	//平行移動

		};
	}



}
#endif