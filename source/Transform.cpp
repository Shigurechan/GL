#include "../header/Transform.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
//#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>



/*#####################################################################################################################################
#  2D Transform
########################################################################################################################################*/
// ##################################### コンストラクタ ##################################### 
FrameWork::D2::Transform::Transform()
{
	position = glm::vec2(0, 0);	//座標
	scale = glm::vec2(1, 1);	//スケール
	rotate = 0.0f;			//回転
	
	//行列を初期化
	matScale = glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f));				//スケール
	matRotate = glm::rotate(0.0f, glm::vec3(0.0, 0.0, 1.0));					//回転
	matTranslation = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, 0.0f));		//平行移動
}

/* ############################################################### 設定 ###############################################################  */

// ##################################### 座標　設定 ##################################### 
void FrameWork::D2::Transform::setPosition(glm::vec2 p)
{
	position = p;
	matTranslation = glm::translate(glm::mat4(1), glm::vec3(p.x, p.y, 0));
}

// ##################################### スケール　設定 ##################################### 
void FrameWork::D2::Transform::setScale(glm::vec2 s)
{
	matScale = glm::scale(glm::mat4(1), glm::vec3(s.x, s.y, 0.0f));
}

// ##################################### 回転　設定 ##################################### 
void FrameWork::D2::Transform::setRotate(float r)
{
	rotate = r;
	matRotate = glm::rotate(glm::mat4(1), r, glm::vec3(0.0, 0.0, 1.0));	//回転	
}

/* ############################################################### 取得 ###############################################################  */

// ##################################### 座標　取得 ##################################### 
glm::vec2 FrameWork::D2::Transform::getPosition()
{
	return position;
}

// ##################################### スケール　取得 ##################################### 
glm::vec2 FrameWork::D2::Transform::getScale()
{
	return scale;
}

// ##################################### 回転　取得 ##################################### 
float FrameWork::D2::Transform::getRotate()
{
	return rotate;
}

/* ############################################################### 行列　取得 ###############################################################  */

// ##################################### 平行移動　行列　取得 ##################################### 
glm::mat4 FrameWork::D2::Transform::getMatTranslation()
{
	return matTranslation;
}

// ##################################### スケール　行列　取得 ##################################### 
glm::mat4 FrameWork::D2::Transform::getMatScale()
{
	return matScale;
}

// ##################################### 回転　行列　取得 ##################################### 
glm::mat4 FrameWork::D2::Transform::getMatRotate()
{
	return matRotate;
}

// ##################################### デストラクタ ##################################### 
FrameWork::D2::Transform::~Transform()
{

}





/*#####################################################################################################################################


#  3D Transform


########################################################################################################################################*/


// ##################################### コンストラクタ ##################################### 
FrameWork::D3::Transform::Transform()
{
	position = glm::vec3(0,0,0);		//座標
	scale = glm::vec3(1,1,1);		//スケール
	rotateAngle = 0.0f;			//回転ラジアン
	rotateVector = glm::vec3(0,0,0);	//回転方向
	

	//行列を初期化
	matScale = glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f));				//スケール
	matRotate = glm::rotate(0.0f, glm::vec3(1.0, 1.0, 1.0));					//回転
	matTranslation = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, 0.0f));		//平行移動
}

/* ############################################################### 設定 ###############################################################  */

// ##################################### 座標　設定 ##################################### 
void FrameWork::D3::Transform::setPosition(glm::vec3 p)
{
	position = p;
	matTranslation = glm::translate(glm::mat4(1), glm::vec3(p.x, p.y,p.z));
}

// ##################################### スケール　設定 ##################################### 
void FrameWork::D3::Transform::setScale(glm::vec3 s)
{
	matScale = glm::scale(glm::mat4(1), glm::vec3(s.x, s.y, s.z));
}

// ##################################### 回転　設定 ##################################### 
void FrameWork::D3::Transform::setRotate(glm::vec3 vec,float r)
{
	rotateAngle = r;
	rotateVector = vec;	
	matRotate = glm::rotate(glm::mat4(1),r, vec);
}

// ##################################### 回転 かけ算　設定 ##################################### 
void FrameWork::D3::Transform::setRotateMult(glm::vec3 vec,float r)
{
	rotateAngle = r;
	rotateVector = vec;	
	matRotate = glm::rotate(glm::mat4(1), r, vec) * matRotate;
}


/* ############################################################### 取得 ###############################################################  */

// ##################################### 座標　取得 ##################################### 
glm::vec3 FrameWork::D3::Transform::getPosition()
{
	return position;
}

// ##################################### スケール　取得 ##################################### 
glm::vec3 FrameWork::D3::Transform::getScale()
{
	return scale;
}

// ##################################### 回転　取得 ##################################### 
glm::vec3 FrameWork::D3::Transform::getRotateVector()
{
	return rotateVector;
}


// ##################################### 回転ラジアン　取得 ##################################### 
float FrameWork::D3::Transform::getRotateAngle()
{
	return rotateAngle;
}

/* ############################################################### 行列　取得 ###############################################################  */

// ##################################### 平行移動　行列　取得 ##################################### 
glm::mat4 FrameWork::D3::Transform::getMatTranslation()
{
	return matTranslation;
}

// ##################################### スケール　行列　取得 ##################################### 
glm::mat4 FrameWork::D3::Transform::getMatScale()
{
	return matScale;
}

// ##################################### 回転　行列　取得 ##################################### 
glm::mat4 FrameWork::D3::Transform::getMatRotate()
{
	return matRotate;
}

// ##################################### デストラクタ ##################################### 
FrameWork::D3::Transform::~Transform()
{
	
}




