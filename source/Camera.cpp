#include "../header/Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../header/Window.hpp"
#include "../header/Init.hpp"

std::shared_ptr<std::vector<FrameWork::D2::VertexAttribute>> FrameWork::Camera::vertex = std::make_shared<std::vector<FrameWork::D2::VertexAttribute>>(0);	//頂点配列

glm::mat4 FrameWork::Camera::scale = glm::mat4();	//拡大縮小
glm::mat4 FrameWork::Camera::rotate = glm::mat4();	//回転
glm::mat4 FrameWork::Camera::translate = glm::mat4();	//平行移動

//描画行列
glm::vec3 FrameWork::Camera::position = glm::vec3(0,0,0);	//座標
glm::vec3 FrameWork::Camera::vecLook = glm::vec3(0,0,-1);	//向き(視線)
glm::mat4 FrameWork::Camera::view = glm::lookAt(glm::vec3(position.x, position.y, position.z), vecLook, glm::vec3(0, 1, 0));	//ビュー行列
glm::mat4 FrameWork::Camera::projection = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.00001f, 10000.0f);			//透視射形行列

// ##################################### 初期化　##################################### 
void FrameWork::Camera::Init()
{
	vertex->resize(6);	//頂点配列を初期化
}


// ##################################### 頂点属性を取得　##################################### 
std::shared_ptr<std::vector<FrameWork::D2::VertexAttribute>> FrameWork::Camera::getVertexAttribute()
{
	return vertex;
}

// ##################################### 座標を設定　##################################### 
void FrameWork::Camera::setPosition(glm::vec3 p)
{
	position = p;	//座標
}

// ##################################### 視線を設定 ##################################### 
void FrameWork::Camera::setLook(glm::vec3 l)
{
	vecLook = l;		//向き

	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 cameraDirection = glm::normalize(position - vecLook);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(vecLook, cameraRight);

	view = glm::lookAt(glm::vec3(position.x, position.y, position.z), position + vecLook,up);
}

// ##################################### 座標を取得 ##################################### 
glm::vec3 FrameWork::Camera::getPosition()
{
	return position;
}

// #####################################　視線を取得 ##################################### 
glm::vec3 FrameWork::Camera::getLook()
{
	return vecLook;
}

// ##################################### 3D ビュー行列を取得　透視射形行列 ##################################### 
glm::mat4 FrameWork::Camera::getViewProjection()
{
	return projection * view;
}

// ##################################### ２D ビュー行列を取得 正射形　##################################### 
glm::mat4 FrameWork::Camera::getProjection_2D()
{
	return glm::ortho(0.0f, FrameWork::windowContext->getSize().x, FrameWork::windowContext->getSize().y, 0.0f, -1.0f, 1.0f);
}

// ###################### デストラクタ ###################### 
FrameWork::Camera::~Camera()
{

}