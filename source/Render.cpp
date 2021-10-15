#include "../header/Render.hpp"

#include "../header/VertexData.hpp"
#include "../header/Help.hpp"
#include "../header/Shader.hpp"

// ##################################### コンストラクタ #####################################
//頂点属性、レンダリングタイプ、頂点数
FrameWork::D2::Render::Render() : Transform()
{
	shader = std::make_shared<FrameWork::Shader>();	//シェーダー
	
	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
}

// ##################################### デストラクタ ##################################### 
FrameWork::D2::Render::~Render()
{

}






/*#####################################################################################################################################


#  3D Render


########################################################################################################################################*/



// ##################################### コンストラクタ #####################################
//頂点属性、レンダリングタイプ、頂点数
FrameWork::D3::Render::Render() : Transform()
{
	shader = std::make_shared<FrameWork::Shader>();	//シェーダー
	
	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	/*
	glGenBuffers(1, &vio);
	glBindBuffer(GL_ARRAY_BUFFER, vio);
	
	
	glGenBuffers(1, &uio);
	glBindBuffer(GL_ARRAY_BUFFER, uio);
	
	
	glGenBuffers(1, &nio);
	glBindBuffer(GL_ARRAY_BUFFER, nio);
	*/

}

// ##################################### デストラクタ ##################################### 
FrameWork::D3::Render::~Render()
{

}
