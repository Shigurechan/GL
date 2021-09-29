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
	
	
	typedef struct
	{
		GLfloat position[2];
		GLfloat uv[2];
		GLfloat normal[3];
		GLfloat color[4];
	}VertexAttribute;
}
#endif

