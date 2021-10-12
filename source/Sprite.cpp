#include "../header/Sprite.hpp"

#include <array>

#include "../header/Render.hpp"
#include "../header/VertexData.hpp"
#include "../header/Shader.hpp"
#include "../header/Resource.hpp"
#include "../header/VertexData.hpp"
#include "../header/Init.hpp"
#include "../header/Shader.hpp"
#include "../header/Window.hpp"
#include "../header/Camera.hpp"

// ##################################### コンストラクタ #####################################
FrameWork::D2::Sprite::Sprite() : Render()
{

	shader->Input(FrameWork::LoadShader("Shader/2D/BasicTexture_D2.vert")->data(), FrameWork::LoadShader("Shader/2D/BasicTexture_D2.frag")->data());

	vertex = FrameWork::Camera::getVertexAttribute();

	//頂点
	GLint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid *)0);
	shader->setBindAttribLocation("vertexPosition");

	//UV
	attrib = shader->getAttribLocation("vertexUV");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid *)(sizeof(GLfloat) * 2));
	shader->setBindAttribLocation("vertexUV");

	/*
      //Normal
      attrib = shader->getAttribLocation("vertexNormal");
      glEnableVertexAttribArray(attrib);
      glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
      glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 4));
      shader->setBindAttribLocation("vertexNormal");
*/
}

// ##################################### テクスチャ 設定 #####################################
void FrameWork::D2::Sprite::InputTexture(FrameWork::TextureFile tex)
{

	glGenTextures(1, &textureID);		     //テクスチャIDの生成
	glBindTexture(GL_TEXTURE_2D, textureID); //IDバインド
	size = tex.size;				     //サイズ

	//テクスチャ生成
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.size.x, tex.size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.fileData);

	// テクスチャの補間設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

// ##################################### 頂点属性 #####################################

void FrameWork::D2::Sprite::setAttribute()
{

	vertex->resize(6);

	// 頂点座標
	vertex->at(0).position[0] = -0.5f;
	vertex->at(0).position[1] = 0.5f;

	vertex->at(1).position[0] = -0.5f;
	vertex->at(1).position[1] = -0.5f;

	vertex->at(2).position[0] = 0.5f;
	vertex->at(2).position[1] = 0.5f;

	vertex->at(3).position[0] = 0.5f;
	vertex->at(3).position[1] = 0.5f;

	vertex->at(4).position[0] = -0.5f;
	vertex->at(4).position[1] = -0.5f;

	vertex->at(5).position[0] = 0.5f;
	vertex->at(5).position[1] = -0.5f;

	//UV座標
	float sizeX = 1.0f / (float)size.x;
	float sizeY = 1.0f / (float)size.y;

	vertex->at(0).uv[0] = sizeX * startSize.x;
	vertex->at(0).uv[1] = sizeY * endSize.y;

	vertex->at(1).uv[0] = sizeX * startSize.x;

	vertex->at(1).uv[1] = sizeY * startSize.y;

	vertex->at(4).uv[0] = sizeX * startSize.x;
	vertex->at(4).uv[1] = sizeY * startSize.y;

	vertex->at(2).uv[0] = sizeX * endSize.x;
	vertex->at(2).uv[1] = sizeY * endSize.y;

	vertex->at(3).uv[0] = sizeX * endSize.x;
	vertex->at(3).uv[1] = sizeY * endSize.y;

	vertex->at(5).uv[0] = sizeX * endSize.x;
	vertex->at(5).uv[1] = sizeY * startSize.y;
}

/*
// ##################################### 法線　設定 ##################################### 	
void FrameWork::Sprite::setNormal(std::array<glm::vec3, 6> n)
{

	vertex->at(0).normal[0] = n.at(0).x;
	vertex->at(0).normal[1] = n.at(0).y;
	vertex->at(0).normal[2] = n.at(0).z;

	vertex->at(1).normal[0] = n.at(1).x;
	vertex->at(1).normal[1] = n.at(1).y;
	vertex->at(1).normal[2] = n.at(1).z;

	vertex->at(2).normal[0] = n.at(2).x;
	vertex->at(2).normal[1] = n.at(2).y;
	vertex->at(2).normal[2] = n.at(2).z;

	vertex->at(3).normal[0] = n.at(3).x;
	vertex->at(3).normal[1] = n.at(3).y;
	vertex->at(3).normal[2] = n.at(3).z;

	vertex->at(4).normal[0] = n.at(4).x;
	vertex->at(4).normal[1] = n.at(4).y;
	vertex->at(4).normal[2] = n.at(4).z;

	vertex->at(5).normal[0] = n.at(5).x;
	vertex->at(5).normal[1] = n.at(5).y;
	vertex->at(5).normal[2] = n.at(5).z;

}
*/

// ##################################### 描画指定 #####################################
void FrameWork::D2::Sprite::Draw(glm::vec2 pos, int texNum, float r, glm::vec2 s, glm::vec2 start, glm::vec2 end)
{
	shader->setEnable();

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	startSize = start; //テクスチャ始点
	endSize = end;	 //テクスチャ終点
	setAttribute();	 //頂点属性　設定

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexAttribute) * vertex->size(), vertex->data());

	//Transform
	setPosition(pos);				  //座標
	setScale(s + glm::vec2(end - start)); //スケール
	setRotate(r);				  //回転

	//描画
	shader->setUniformMatrix4fv("uTranslate",getMatTranslation());
	shader->setUniformMatrix4fv("uRotate", getMatRotate());
	shader->setUniformMatrix4fv("uScale", getMatScale());
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::windowContext->getSize().x, FrameWork::windowContext->getSize().y, 0.0f, -1.0f, 1.0f));

	glActiveTexture(GL_TEXTURE0);		     //テクスチャ有効
	glBindTexture(GL_TEXTURE_2D, textureID); //テクスチャバインド

	glDrawArrays(GL_TRIANGLES, 0, vertex->size()); //描画

	//バインド解除
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader->setDisable();
}

// ##################################### デストラクタ #####################################
FrameWork::D2::Sprite::~Sprite()
{
}