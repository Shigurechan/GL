#include "../header/Line.hpp"

#include "../header/Init.hpp"
#include "../header/Window.hpp"
#include "../header/Shader.hpp"
#include "../header/Camera.hpp"

// ##################################### コンストラクタ ##################################### 
FrameWork::Line::Line() : Render_2D()
{	
	vertex = FrameWork::Camera_2D::getVertexAttribute();
	vertex->resize(2);

	//頂点	
	GLint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	shader->setBindAttribLocation("vertexPosition");

}

// ##################################### 描画 ##################################### 
void FrameWork::Line::Draw(glm::vec2 start, glm::vec2 end,glm::vec4 color,unsigned short width, float r)
{

	glLineWidth(width);  //太さ
	glm::vec2 size = glm::abs(end - start) / 2.0f;
	vertex->at(0).position[0] = -size.x;
	vertex->at(0).position[1] = -size.y;

	vertex->at(1).position[0] = +size.x;
	vertex->at(1).position[1] = +size.y;

	//Transform
	setPosition(glm::vec2(FrameWork::windowContext->getSize().x / 2, FrameWork::windowContext->getSize().y / 2));	//座標
	setScale(glm::vec2(1,1));							  								//スケール
	setRotate(r);																	//回転

	shader->setEnable();
	shader->setUniformMatrix4fv("uTranslate", getMatTranslation());
	shader->setUniformMatrix4fv("uRotate", getMatRotate());
	shader->setUniformMatrix4fv("uScale", getMatScale());
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::windowContext->getSize().x, FrameWork::windowContext->getSize().y, 0.0f, -1.0f, 1.0f));
	shader->setUniform4f("uFragment",color);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexAttribute) * vertex->size(), vertex->data());
	glDrawArrays(GL_LINES, 0, vertex->size());
	shader->setDisable();
}

// ##################################### デストラクタ ##################################### 
FrameWork::Line::~Line()
{
	
}