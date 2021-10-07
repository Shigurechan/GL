/*#########################################################################
#
###########################################################################*/
#version 420
//#extension GL_ARB_explicit_uniform_location : require

// ######################  ###################### 
layout(location = 0) in vec2 vertexPosition;	
layout(location = 1) in vec2 vertexUV;		


// ###################### ###################### 
layout(location = 1) out vec2 texCoord;

// ###################### Uniform ###################### 
uniform mat4 uViewProjection;	

void main()
{

	vec4 vertex = vec4(vertexPosition.x,vertexPosition.y,0.0,1.0);	
	gl_Position =  (uViewProjection * vertex);
	
	texCoord = vertexUV;

}