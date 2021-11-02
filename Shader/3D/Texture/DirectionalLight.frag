/*#########################################################################
# 
###########################################################################*/
#version 420
//#extension GL_ARB_explicit_uniform_location : require

layout(location = 3) in vec3 vPosition;
layout(location = 4) in vec2 vUV;
layout(location = 5) in vec3 vNormal;

struct Material 
{
    sampler2D texture;
    vec3 specular;    
    float shininess;
}; 

struct Light 
{
	vec3 direction;
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
	vec3 ambient = light.ambient * texture(material.texture,vUV).rgb;
  	
    	// diffuse 
	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.texture,vUV).rgb;

	// specular
	vec3 viewDir = normalize(uViewPosition - vPosition);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
      vec3 specular = light.specular * spec * material.specular;  


	vec3 result = ambient + diffuse + specular;
	fragment = vec4(result, 1.0);
}
