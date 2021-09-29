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
#include "Transform_2D.hpp"

namespace FrameWork
{
	class Render_2D : public Transform_2D
	{
	public:
		
		Render_2D();	//コンストラクタ
		~Render_2D();	//デストラクタ

		std::shared_ptr<FrameWork::Shader> shader;	//シェーダー

	protected:
		
		std::shared_ptr<std::vector<VertexAttribute>> vertex;	//頂点情報

	};
};

#endif
