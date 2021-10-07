/*#########################################################################
#
###########################################################################*/
#version 420




// ######################  ###################### 
layout(location = 0) in vec2 vertexPosition;	
layout(location = 1) in vec2 vertexUV;		

// ######################  ###################### 
layout(location = 2) out vec2 vUV; //UV

// ###################### Uniform ###################### 
uniform mat4 uScale;		
uniform mat4 uRotate;		
uniform mat4 uTranslate;	

uniform mat4 uViewProjection;	

void main()
{
	vec4 vertex = vec4(vertexPosition,0.0,1.0);		
	mat4 model = uTranslate * uRotate * uScale;		
	gl_Position = (uViewProjection * model) * vertex;
	
	vUV = vertexUV;	
}
