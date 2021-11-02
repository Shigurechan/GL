/*#########################################################################
# 
###########################################################################*/
#version 420
//#extension GL_ARB_explicit_uniform_location : require


layout(location = 0) in vec3 vertexPosition;	
//layout(location = 1) in vec2 vertexUV;	
//layout(location = 2) in vec3 vertexNormal;	


//layout(location = 3) out vec2 vUV;	
layout(location = 1) out vec4 vFragment;	
//layout(location = 4) out vec3 vNormal;	



uniform mat4 uTranslate;	
uniform mat4 uRotate;		
uniform mat4 uScale;		
uniform mat4 uViewProjection;	

uniform vec4 uFragment;


void main()
{
	vec4 vertex = vec4(vertexPosition,1.0);
	mat4 model = uTranslate * uRotate * uScale;		
	gl_Position = (uViewProjection * model) * vertex;
	


//	vUV = vertexUV;		
	vFragment = uFragment;
//	vNormal = vertexNormal;		
}