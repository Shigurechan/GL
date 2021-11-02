/*#########################################################################
# 
###########################################################################*/
#version 420
//#extension GL_ARB_explicit_uniform_location : require

layout(location = 2) in vec3 vPosition;
layout(location = 3) in vec3 vNormal;

//マテリアル
struct Material 
{
      vec3 ambient;
      vec3 diffuse;
      vec3 specular;    
      float shininess;

//      uniform float uAmbientStrength;	//環境光の強さ
//      uniform float uSpecularStrength;	//鏡面反射の強さ
//      uniform float uBrightStrength;	//反射輝度の強さ

}; 

//ライト
struct Light 
{
      vec3 position;

      vec3 ambient;
      vec3 diffuse;
      vec3 specular;
};



uniform Material material;    //マテリアル
uniform Light light;          //ライト
uniform vec3 uViewPosition;	//カメラ座標


out vec4 fragment;

void main()
{
	
   	// ambient
//	float ambientStrength = 0.1;
	vec3 ambient = material.ambient * light.ambient;
  	
    	// diffuse 
	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(light.position - vPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	// specular
	//float specularStrength = 0.5;
	vec3 viewDir = normalize(uViewPosition - vPosition);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
      vec3 specular = light.specular * (spec * material.specular);  

	vec3 result = ambient + diffuse + specular;
	fragment = vec4(result, 1.0);
}
