#ifndef ___RENDER_HPP_
#define ___RENDER_HPP_
#include <iostream>
#include <memory>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>

#include "Shader.hpp"
#include "VertexData.hpp"
#include "Transform.hpp"

namespace FrameWork
{
	namespace D2
	{
		class Render : public FrameWork::D2::Transform
		{
			public:
				
				Render();	//コンストラクタ
				~Render();	//デストラクタ

				std::shared_ptr<FrameWork::Shader> shader;	//シェーダー

			protected:
				
				std::shared_ptr<std::vector<VertexAttribute>> vertex;	//頂点情報

				GLuint vao;	//VertexArrayObject
				GLuint vbo;	//VertexBufferObject	
			
		};
	}


	namespace D3
	{
		class Render : public FrameWork::D3::Transform
		{
			public:
				
				Render();	//コンストラクタ
				~Render();	//デストラクタ

				Shader *shader;

			protected:
				
				GLuint vao;	//VertexArrayObject
				GLuint vbo;	//VertexBufferObject	
				GLuint eao;	//VertexIndexObject;



			
		};
	}
	
}

#endif
