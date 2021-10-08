#include "../header/Triangle.hpp"

#include "../header/Init.hpp"
#include "../header/Window.hpp"
#include "../header/Shader.hpp"
#include "../header/VertexData.hpp"
#include "../header/Render.hpp"
#include "../header/Camera.hpp"
#include "../header/Resource.hpp"

// ##################################### コンストラクタ ##################################### 
FrameWork::Triangle::Triangle() : Render_2D()
{


	shader->Input(FrameWork::LoadShader("Shader/2D/BasicMono_2D.vert")->data(),FrameWork::LoadShader("Shader/2D/BasicMono_2D.frag")->data());




	vertex = FrameWork::Camera_2D::getVertexAttribute();
	vertex->resize(3);

	//頂点	
	GLint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	shader->setBindAttribLocation("vertexPosition");












}

// ##################################### 描画 設定 ##################################### 
void FrameWork::Triangle::Draw(const glm::vec2 pos,const glm::vec2 s,const glm::ivec4 color,GLfloat r)
{

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	vertex->resize(3);

	vertex->at(0).position[0] = 0;
	vertex->at(0).position[1] = -(s.y / 2.0f);

	vertex->at(1).position[0] = -(s.x / 2.0f);
	vertex->at(1).position[1] = +(s.y / 2.0f);

	vertex->at(2).position[0] = +(s.x / 2.0f);
	vertex->at(2).position[1] = +(s.y / 2.0f);

	setPosition(glm::vec2(pos.x + (s.x / 2), pos.y + (s.y / 2)));	//座標
	setRotate(r);									//回転
	setScale(glm::vec2(1,1));							//スケール

	shader->setEnable();
	shader->setUniformMatrix4fv("uTranslate", getMatTranslation());
	shader->setUniformMatrix4fv("uRotate", getMatRotate());
	shader->setUniformMatrix4fv("uScale", getMatScale());
	shader->setUniform4f("uFragment",color );
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::windowContext->getSize().x, FrameWork::windowContext->getSize().y, 0.0f, -1.0f, 1.0f));

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexAttribute) * vertex->size(), vertex->data());
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertex->size());
	shader->setDisable();

	//バインド解除
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// ##################################### デストラクタ ##################################### 
FrameWork::Triangle::~Triangle()
{
	
}