/*#########################################################################
# 
###########################################################################*/
#version 420
//#extension GL_ARB_explicit_uniform_location : require

layout(location = 2) in vec3 fPosition;
layout(location = 3) in vec3 fNormal;


uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

out vec4 fragment;

void main()
{

	
   	// ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;
  	
    	// diffuse 
	vec3 norm = normalize(fNormal);
	vec3 lightDir = normalize(lightPos - fPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;


	// specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - fPosition);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  


	vec3 result = (ambient + diffuse) * objectColor;
	fragment = vec4(result, 1.0);
}

