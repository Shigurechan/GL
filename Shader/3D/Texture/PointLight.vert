/*#########################################################################
# 
###########################################################################*/
#version 420
//#extension GL_ARB_explicit_uniform_location : require


layout(location = 0) in vec3 vertexPosition;	
layout(location = 1) in vec2 vertexUV;	
layout(location = 2) in vec3 vertexNormal;	


uniform mat4 uTranslate;	
uniform mat4 uRotate;		
uniform mat4 uScale;		
uniform mat4 uViewProjection;	


layout(location = 3) out vec3 vPosition;
layout(location = 4) out vec2 vUV;
layout(location = 5) out vec3 vNormal;


void main()
{
	vec4 vertex = vec4(vertexPosition,1.0);
	mat4 model = uTranslate * uRotate * uScale;		
	gl_Position = (uViewProjection * model) * vertex;
	
	vPosition = vec3(model * vec4(vertexPosition,1.0));
	vNormal = mat3(transpose(inverse(model))) * vertexNormal;
      vUV = vertexUV;


}