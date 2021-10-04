#include "../header/Ellipse.hpp"

#include "../header/Render.hpp"
#include "../header/VertexData.hpp"
#include "../header/Init.hpp"
#include "../header/Window.hpp"
#include "../header/Shader.hpp"
#include "../header/Camera.hpp"

// ##################################### コンストラクタ ##################################### 
FrameWork::Ellipse::Ellipse() : Render_2D()
{	
	
	vertNum = 0;		//頂点数
	vertex = FrameWork::Camera_2D::getVertexAttribute();
	
}
// ##################################### 描画　設定 ##################################### 
void FrameWork::Ellipse::Draw(glm::vec2 pos, glm::vec4 color,glm::vec2 s, int num,float r)
{

	if (vertNum != num)
	{
		vertNum = num;
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

	shader->setEnable();
	shader->setUniformMatrix4fv("uTranslate", getMatTranslation());
	shader->setUniformMatrix4fv("uRotate", getMatRotate());
	shader->setUniformMatrix4fv("uScale", getMatScale());
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::windowContext->getSize().x, FrameWork::windowContext->getSize().y, 0.0f, -1.0f, 1.0f));
	shader->setUniform4f("uFragment",color);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertex->size());
	shader->setDisable();

}

// ##################################### デストラクタ ##################################### 
FrameWork::Ellipse::~Ellipse()
{
	
}