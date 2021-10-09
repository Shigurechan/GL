#include "../header/Line.hpp"

#include "../header/Init.hpp"
#include "../header/Window.hpp"
#include "../header/Shader.hpp"
#include "../header/Camera.hpp"
#include "../header/Resource.hpp"

// ##################################### コンストラクタ ##################################### 
FrameWork::Line::Line() : Render_2D()
{	
	shader->Input(FrameWork::LoadShader("Shader/2D/BasicMono_2D.vert")->data(),FrameWork::LoadShader("Shader/2D/BasicMono_2D.frag")->data());

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
FrameWork::Line::~Line()
{
	
}