#include "../header/Shape.hpp"

#include <iostream>

#include "../header/VertexData.hpp"
#include "../header/Render.hpp"
#include "../header/Camera.hpp"
#include "../header/Resource.hpp"
#include "../header/Shader.hpp"
#include "../header/Init.hpp"
#include "../header/Window.hpp"


/*#####################################################################################################################################
#  円
########################################################################################################################################*/
// ##################################### コンストラクタ ##################################### 
FrameWork::D2::Circle::Circle() : Render()
{
	shader->Input(FrameWork::LoadShader("Shader/D2/BasicMono_D2.vert")->data(),FrameWork::LoadShader("Shader/D2/BasicMono_D2.frag")->data());
	vertex = FrameWork::Camera::getVertexAttribute();
}

// ##################################### 描画 ##################################### 
void FrameWork::D2::Circle::Draw(const glm::vec2 pos, const glm::vec4 color,const GLushort num, const GLushort w, const GLfloat r)
{	

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	if (vertex->size() != num)
	{
		vertex->resize(num);

		//頂点	
		GLint attrib = shader->getAttribLocation("vertexPosition");
		glEnableVertexAttribArray(attrib);
		glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat),(GLvoid*)0);
	}
	//Transform
	setPosition(pos);			//座標
	setScale(glm::vec2(1, 1));	//スケール
	setRotate(r);			//回転
	
	shader->setEnable();
	shader->setUniformMatrix4fv("uTranslate", getMatTranslation());
	shader->setUniformMatrix4fv("uRotate", getMatRotate());
	shader->setUniformMatrix4fv("uScale", getMatScale());
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::windowContext->getSize().x, FrameWork::windowContext->getSize().y, 0.0f, -1.0f, 1.0f));
	shader->setUniform4f("uFragment",color);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexAttribute) * vertex->size(), vertex->data());
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertex->size());
	shader->setDisable();

	//バインド解除
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// ##################################### デストラクタ ##################################### 
FrameWork::D2::Circle::~Circle()
{
	
}

/*#####################################################################################################################################
#  点
########################################################################################################################################*/
// ##################################### コンストラクタ ##################################### 
FrameWork::D2::Point::Point() : Render()
{

	shader->Input(FrameWork::LoadShader("Shader/D2/BasicMono_D2.vert")->data(),FrameWork::LoadShader("Shader/D2/BasicMono_D2.frag")->data());
	
	vertex = FrameWork::Camera::getVertexAttribute();

	//頂点	
	GLint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	shader->setBindAttribLocation("vertexPosition");
}

// ##################################### 描画 ##################################### 
void FrameWork::D2::Point::Draw(glm::vec2 p,glm::vec4 color,unsigned short s)
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
FrameWork::D2::Point::~Point()
{
	
}

/*#####################################################################################################################################
#  線
########################################################################################################################################*/
// ##################################### コンストラクタ ##################################### 
FrameWork::D2::Line::Line() : Render()
{	
	shader->Input(FrameWork::LoadShader("Shader/D2/BasicMono_D2.vert")->data(),FrameWork::LoadShader("Shader/D2/BasicMono_D2.frag")->data());

	vertex = FrameWork::Camera::getVertexAttribute();
	vertex->resize(2);

	//頂点	
	GLint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	shader->setBindAttribLocation("vertexPosition");

}

// ##################################### 描画 ##################################### 
void FrameWork::D2::Line::Draw(glm::vec2 start, glm::vec2 end,glm::vec4 color,unsigned short width, float r)
{

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	vertex->resize(2);

	glLineWidth(width);  //太さ
	glm::vec2 size = glm::abs(glm::vec2(end.x - start.x,end.y - start.y)) / 2.0f;
	glm::vec2 center = glm::vec2(end.x + start.x,end.y + start.y) / 2.0f;


	vertex->at(0).position[0] = start.x;
	vertex->at(0).position[1] = start.y;			
	
	vertex->at(1).position[0] = end.x;
	vertex->at(1).position[1] = end.y;			


	vertex->at(0).position[0] += -center.x;
	vertex->at(0).position[1] += -center.y;			
	
	vertex->at(1).position[0] += -center.x;
	vertex->at(1).position[1] += -center.y;

	glm::vec2 st;
	glm::vec2 en;
	st.x = (cos(r) * (vertex->at(0).position[0])) + (-sin(r) * (vertex->at(0).position[1]));
	st.y = (sin(r) * (vertex->at(0).position[0])) + (cos(r) * (vertex->at(0).position[1]));

	en.x = (cos(r) * (vertex->at(1).position[0])) + (-sin(r) * (vertex->at(1).position[1]));
	en.y = (sin(r) * (vertex->at(1).position[0])) + (cos(r) * (vertex->at(1).position[1]));


	vertex->at(0).position[0] = st.x + center.x;
	vertex->at(0).position[1] = st.y + center.y;			

	vertex->at(1).position[0] = en.x + center.x;
	vertex->at(1).position[1] = en.y + center.y;			



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
	glDrawArrays(GL_LINES, 0, vertex->size());
	shader->setDisable();

	//バインド解除
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

// ##################################### デストラクタ ##################################### 
FrameWork::D2::Line::~Line()
{
	
}

/*#####################################################################################################################################
#  三角形
########################################################################################################################################*/
// ##################################### コンストラクタ ##################################### 
FrameWork::D2::Triangle::Triangle() : Render()
{
	shader->Input(FrameWork::LoadShader("Shader/D2/BasicMono_D2.vert")->data(),FrameWork::LoadShader("Shader/D2/BasicMono_D2.frag")->data());

	vertex = FrameWork::Camera::getVertexAttribute();
	vertex->resize(3);

	//頂点	
	GLint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	shader->setBindAttribLocation("vertexPosition");
}

// ##################################### 描画 設定 ##################################### 
void FrameWork::D2::Triangle::Draw(const glm::vec2 pos,const glm::vec2 s,const glm::ivec4 color,GLfloat r)
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
FrameWork::D2::Triangle::~Triangle()
{
	
}

/*#####################################################################################################################################
#  矩形
########################################################################################################################################*/
// ##################################### コンストラクタ ##################################### 
FrameWork::D2::Rectangle::Rectangle() : Render()
{		
	shader->Input(FrameWork::LoadShader("Shader/D2/BasicMono_D2.vert")->data(),FrameWork::LoadShader("Shader/D2/BasicMono_D2.frag")->data());
	
	vertex = FrameWork::Camera::getVertexAttribute();
	vertex->resize(6);

	//頂点	
	GLint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	shader->setBindAttribLocation("vertexPosition");

}

// ##################################### 描画 ##################################### 
void FrameWork::D2::Rectangle::Draw(glm::vec2 start,glm::vec2 end,glm::vec4 color,float r)
{

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

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

	//Transform
	setPosition(start);		//座標
	setScale(end - start);		//スケール
	setRotate(r);			//回転


	shader->setEnable();
	shader->setUniformMatrix4fv("uTranslate", getMatTranslation());
	shader->setUniformMatrix4fv("uRotate", getMatRotate());
	shader->setUniformMatrix4fv("uScale", getMatScale());
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::windowContext->getSize().x, FrameWork::windowContext->getSize().y, 0.0f, -1.0f, 1.0f));
	shader->setUniform4f("uFragment",color);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexAttribute) * vertex->size(), vertex->data());
	glDrawArrays(GL_TRIANGLES, 0, vertex->size());
	shader->setDisable();

	//バインド解除
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// ##################################### デストラクタ ##################################### 
FrameWork::D2::Rectangle::~Rectangle()
{
	
}

/*#####################################################################################################################################
#  楕円
########################################################################################################################################*/
// ##################################### コンストラクタ ##################################### 
FrameWork::D2::Ellipse::Ellipse() : Render()
{	
	
	shader->Input(FrameWork::LoadShader("Shader/D2/BasicMono_D2.vert")->data(),FrameWork::LoadShader("Shader/D2/BasicMono_D2.frag")->data());

	vertNum = 0; //頂点数
	vertex = FrameWork::Camera::getVertexAttribute();
	
}
// ##################################### 描画　設定 ##################################### 
void FrameWork::D2::Ellipse::Draw(glm::vec2 pos, glm::vec4 color,glm::vec2 s, int num,float r)
{
	shader->setEnable();

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	if (vertex->size() != num)
	{
		
		vertex->resize(num);
		//頂点	
		GLint attrib = shader->getAttribLocation("vertexPosition");
		glEnableVertexAttribArray(attrib);
		glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
		shader->setBindAttribLocation("vertexPosition");
	
	}

	float r2 = (float)((PI * 2.0) / (double)vertex->size());
	float rr = 0;
	for (int i = 0; i < vertex->size(); i++)
	{
		vertex->at(i).position[0] = (cos(rr) * s.x);
		vertex->at(i).position[1] = (sin(rr) * s.y);		
		rr += r2;
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexAttribute) * vertex->size(), vertex->data());

	//Transform
	setPosition(pos);				//座標
	setScale(glm::vec2(1,1));		//スケール
	setRotate(r);				//回転

	shader->setUniformMatrix4fv("uTranslate", getMatTranslation());
	shader->setUniformMatrix4fv("uRotate", getMatRotate());
	shader->setUniformMatrix4fv("uScale", getMatScale());
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::windowContext->getSize().x, FrameWork::windowContext->getSize().y, 0.0f, -1.0f, 1.0f));
	shader->setUniform4f("uFragment",color);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertex->size());
	shader->setDisable();


	//バインド解除
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// ##################################### デストラクタ ##################################### 
FrameWork::D2::Ellipse::~Ellipse()
{
	
}