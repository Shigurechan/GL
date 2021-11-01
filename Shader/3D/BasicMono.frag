/*#########################################################################
# 
###########################################################################*/
#version 420
//#extension GL_ARB_explicit_uniform_location : require


//layout(location = 3) in vec2 vUV;	
layout(location = 1) in vec4 vfragment;	

//layout(location = 4) in vec3 vNormal;	



//uniform sampler2D uImage;	
out vec4 fragment;

void main()
{
	fragment = vfragment;
//	fragment = texture(uImage,vUV);
}