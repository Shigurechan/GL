/*#########################################################################
# 
###########################################################################*/
#version 420
//#extension GL_ARB_explicit_uniform_location : require

// ###################### ###################### 
layout(location = 1 ) in vec2 texCoord;

// ######################  ###################### 
out vec4 color;

// ###################### Unifrom ###################### 
uniform sampler2D text;   
uniform vec4 uFragment;   

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoord).r);
    color = uFragment * sampled;
}  