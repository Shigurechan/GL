#include "../header/Point.hpp"

#include "../header/Init.hpp"
#include "../header/Window.hpp"
#include "../header/Shader.hpp"
#include "../header/Camera.hpp"
#include "../header/Resource.hpp"

// ##################################### コンストラクタ ##################################### 
FrameWork::Point::Point() : Render_2D()
{

	shader->Input(FrameWork::LoadShader("Shader/2D/BasicMono_2D.vert")->data(),FrameWork::LoadShader("Shader/2D/BasicMono_2D.frag")->data());
	
	vertex = FrameWork::Camera_2D::getVertexAttribute();
	vertex->resize(1);

	//頂点	
	GLint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	shader->setBindAttribLocation("vertexPosition");

	
}

// ##################################### 描画 ##################################### 
void FrameWork::Point::Draw(glm::vec2 p,glm::vec4 color,unsigned short s)
{

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	vertex->resize(1);	
	glPointSize(s);		//サイズ

	vertex->at(0).position[0] = p.x;
	vertex->at(0).position[1] = p.y;

	//Transform
	setPosition(glm::vec2(0,0));	//座標
	setScale(glm::vec2(1,1));	//スケール
	setRotate(0);			//回転

	shader->setEnable();
	shader->setUniformMatrix4fv("uTranslate", getMatTranslation());
	shader->setUniformMatrix4fv("uRotate", getMatRotate());
	shader->setUniformMatrix4fv("uScale", getMatScale());
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::windowContext->getSize().x, FrameWork::windowContext->getSize().y, 0.0f, -1.0f, 1.0f));
	shader->setUniform4f("uFragment",color);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexAttribute) * vertex->size(), vertex->data());
	glDrawArrays(GL_POINTS, 0, vertex->size());
	shader->setDisable();

	//バインド解除
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}





// ##################################### デストラクタ ##################################### 
FrameWork::Point::~Point()
{
	
}