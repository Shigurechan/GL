#ifndef ___CAMERA_HPP_
#define ___CAMERA_HPP_
#include <iostream>
#include <glm/glm.hpp>
#include "VertexData.hpp"
#include "Render.hpp"
#include "Actor.hpp"
/*#########################################################################
# Cameraクラス

説明
	
###########################################################################*/
namespace FrameWork
{
	class Window;

	class Camera
	{

	public:

		static void Init();	//初期化
		~Camera();		//デストラクタ


		// ###################### 設定　関係 ###################### 
		static void setPosition(glm::vec3 p);	//座標
		static void setLook(glm::vec3 l);		//視線

		// ###################### 取得　関係 ###################### 
		static glm::vec3 getPosition();	//座標
		static glm::vec3 getLook();		//視線

		static GLuint getVao();
		static GLuint getVbo();

		static std::shared_ptr<std::vector<FrameWork::D2::VertexAttribute>> getVertexAttribute();	//頂点属性を取得

		//カメラ行列を取得
		static glm::mat4 getViewProjection();		//3Dカメラ
		static glm::mat4 getProjection_2D();		//2Dカメラ

		static void setScale(glm::vec2 s);			//スケール
		static void setRotate(float a);			//回転
		static void setTranslate(glm::vec3 t);		//平行移動
		


		//static glm::vec2 getSizeScale();			//サイズを取得
		//static void setSizeScale(glm::vec2 s);		//サイズを設定

	private:

		static std::shared_ptr<std::vector<FrameWork::D2::VertexAttribute>> vertex;	//頂点配列

		//描画行列
		static glm::mat4 scale;		//拡大縮小
		static glm::mat4 rotate;	//回転
		static glm::mat4 translate;	//平行移動

		static glm::vec3 position;	//座標
		static glm::vec3 vecLook;	//向き(視線)
		static glm::mat4 view;		//ビュー行列
		static glm::mat4 projection;	//透視射形行列

		Camera();	//コンストラクタ
	};
}
#endif