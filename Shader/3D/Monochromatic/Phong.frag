/*#########################################################################
# 
###########################################################################*/
#version 420
//#extension GL_ARB_explicit_uniform_location : require

layout(location = 2) in vec3 vPosition;
layout(location = 3) in vec3 vNormal;


uniform vec3 uLightPosition;		//ライト座標 
uniform vec3 uLightColor;		//ライト色
uniform vec3 uObjectColor;		//オブジェクトの色
uniform vec3 uViewPosition;		//カメラ座標

uniform float uAmbientStrength;	//環境光の強さ
uniform float uSpecularStrength;	//鏡面反射の強さ
uniform float uShininessStrength;	//反射輝度の強さ

out vec4 fragment;

void main()
{
	
   	// ambient
//	float ambientStrength = 0.1;
	vec3 ambient = uAmbientStrength * uLightColor;
  	
    	// diffuse 
	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(uLightPosition - vPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * uLightColor;

	// specular
	//float specularStrength = 0.5;
	vec3 viewDir = normalize(uViewPosition - vPosition);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininessStrength);
	vec3 specular = uSpecularStrength * spec * uLightColor;  


	vec3 result = (ambient + diffuse + specular) * uObjectColor;
	fragment = vec4(result, 1.0);
}

