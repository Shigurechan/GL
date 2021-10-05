#include "../header/Circle.hpp"

#include "../header/VertexData.hpp"
#include "../header/Window.hpp"
#include "../header/Init.hpp"
#include "../header/Render.hpp"
#include "../header/Camera.hpp"
#include "../header/Resource.hpp"

// ##################################### コンストラクタ ##################################### 
FrameWork::Circle::Circle() : Render_2D()
{

	shader->Input(FrameWork::LoadShader("Shader/2D/BasicMono_2D.vert")->data(),FrameWork::LoadShader("Shader/2D/BasicMono_2D.frag")->data());
	
	vertex = FrameWork::Camera_2D::getVertexAttribute();

	
	vertNum = 0;

}

// ##################################### 描画 ##################################### 
void FrameWork::Circle::Draw(const glm::vec2 pos, const glm::vec4 color,const GLushort num, const GLushort w, const GLfloat r)
{	

	if (vertNum != num)
	{
		vertex->resize(num);
		vertNum = num;


		//頂点	
		GLint attrib = shader->getAttribLocation("vertexPosition");
		glEnableVertexAttribArray(attrib);
		glBufferData(GL_ARRAY_BUFFER, vertex->size() * sizeof(VertexAttribute), vertex->data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat),(GLvoid*)0);
		shader->setBindAttribLocation("vertexPosition");
	}

	float n = (PI * 2.0f) / (float)vertex->size();
	float t = 0.0f;
	for (int i = 0; i < vertex->size(); i++)
	{
		vertex->at(i).position[0] = cos(t) * w;
		vertex->at(i).position[1] = sin(t) * w;

		t += n;
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

}

// ##################################### デストラクタ ##################################### 
FrameWork::Circle::~Circle()
{
	
}