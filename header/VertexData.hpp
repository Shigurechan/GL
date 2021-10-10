#ifndef VERTEX_DATA_HPP_
#define VERTEX_DATA_HPP_

/*#########################################################################
# Vertex

説明
	頂点情報
###########################################################################*/

#include <GL/glew.h>

namespace FrameWork 
{
	namespace D2
	{
		typedef struct vertex_attribute
		{
			GLfloat position[2];
			GLfloat uv[2];
			GLfloat normal[3];
			GLfloat color[4];
		}VertexAttribute;

	}

	namespace D3
	{
		typedef struct vertex_attribute
		{
			GLfloat position[3];
			GLfloat uv[2];
			GLfloat normal[3];
		}VertexAttribute;



		typedef struct vertex_attribute_color
		{
			GLfloat position[3];
			GLfloat uv[2];
			GLfloat color[4];
		}VertexAttribute_Color;
		
		typedef struct vertex_attribute_normalColor
		{
			GLfloat position[3];
			GLfloat uv[2];
			GLfloat normal[3];
			GLfloat color[4];
		}VertexAttribute_NormalColor;
		

	}


}
#endif

