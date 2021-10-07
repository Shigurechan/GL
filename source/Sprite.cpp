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
FrameWork::Sprite::Sprite(const char* vert, const char* frag) : Render_2D()
{
	glEnable(GL_TEXTURE_2D);

	shader->Input(FrameWork::LoadShader("Shader/2D/BasicTexture_2D.vert")->data(),FrameWork::LoadShader("Shader/2D/BasicTexture_2D.frag")->data());


	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	vertex = FrameWork::Camera_2D::getVertexAttribute();

      //頂点	
      GLint attrib = shader->getAttribLocation("vertexPosition");
      glEnableVertexAttribArray(attrib);
      glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
      glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
      shader->setBindAttribLocation("vertexPosition");


      //UV
      attrib = shader->getAttribLocation("vertexUV");
      glEnableVertexAttribArray(attrib);
      glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
      glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
      shader->setBindAttribLocation("vertexUV");


/*
      //Normal
      attrib = shader->getAttribLocation("vertexNormal");
      glEnableVertexAttribArray(attrib);
      glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
      glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 4));
      shader->setBindAttribLocation("vertexNormal");
	printf("ddddddddd\n");
*/

	texture.clear();	//テクスチャデータ
}

// ##################################### テクスチャ 設定 ##################################### 
void FrameWork::Sprite::InputTexture(FrameWork::TextureFile tex)
{
	//glPixelStorei(GL_PACK_ALIGNMENT, 4);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	Texture data;
	data.size = tex.size;
	data.data = tex.fileData;

//	printf("data.size.x %f\n",data.size.x);
//	printf("data.size.y %f\n\n",data.size.y);
//	printf("data.data %d\n\n",data.data);


	texture.push_back(data);	//テクスチャーIDに追加	


	glGenTextures(1, &texture.back().ID);			//テクスチャIDの生成
	glBindTexture(GL_TEXTURE_2D, texture.back().ID);	//IDをバインド

	// テクスチャの補間設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//テクスチャ生成
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.back().size.x, texture.back().size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.back().data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	texture.back().unitNumber = GL_TEXTURE0 + (int)textureUnitCount;

	//テクスチャユニットを設定できない場合はエラー
	assert(texture.back().unitNumber < GL_TEXTURE31);




//	printf("data.size.x %f\n",texture.back().size.x);
//	printf("data.size.y %f\n\n",texture.back().size.y);

	textureUnitCount++;	//テクスチャーユニットカウントに加算
}


// ##################################### 頂点属性 ##################################### 	

void FrameWork::Sprite::setAttribute()
{

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

	
//	printf("texture.at(textureNumber).size.x %f\n",texture.at(textureNumber).size.x);
	//printf("texture.at(textureNumber).size.y %f\n\n",texture.at(textureNumber).size.y);


	//UV座標
	float sizeX = 1.0f / (float)texture.at(textureNumber).size.x;
	float sizeY = 1.0f / (float)texture.at(textureNumber).size.y;

	//printf("sizeX %f\n",sizeX);
	//printf("sizeY %f\n\n",sizeY);


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

// ##################################### 描画指定 ##################################### 	
void FrameWork::Sprite::Draw(glm::vec2 pos, int texNum, float r, glm::vec2 s, glm::vec2 start, glm::vec2 end)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	startSize = start;	      //テクスチャ始点
	endSize = end;		      //テクスチャ終点
      textureNumber = texNum;	      //テクスチャ指定
	setAttribute();		      //頂点属性　設定

	glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(VertexAttribute) * vertex->size(),vertex->data());

	//Transform
	setPosition(pos);					//座標
	setScale(s + glm::vec2(end - start));	//スケール
	setRotate(r);					//回転

	//描画
      shader->setEnable();
	shader->setUniformMatrix4fv("uTranslate", getMatTranslation());
	shader->setUniformMatrix4fv("uRotate", getMatRotate());
	shader->setUniformMatrix4fv("uScale", getMatScale());
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::windowContext->getSize().x, FrameWork::windowContext->getSize().y, 0.0f, -1.0f, 1.0f));
      shader->setDisable();

	glActiveTexture(texture.at(textureNumber).unitNumber);	//テクスチャを有効にする
	glBindTexture(GL_TEXTURE_2D, texture.at(textureNumber).ID);	//テクスチャをバインド
	
	glDrawArrays(GL_TRIANGLES, 0, vertex->size());

	//バインド解除
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

// ##################################### デストラクタ ##################################### 
FrameWork::Sprite::~Sprite()
{

}