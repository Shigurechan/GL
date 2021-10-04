/*#########################################################################
#  単色の二次元描画　頂点シェーダー
###########################################################################*/
#version 330

#extension GL_ARB_explicit_attrib_location: enable 

// ######################  ###################### 
layout(location = 2) in vec2 vUV;	

// ###################### Unifrom ###################### 
uniform sampler2D uImage;		


out vec4 fragment;

void main()
{
	fragment = texture(uImage,vUV);
}