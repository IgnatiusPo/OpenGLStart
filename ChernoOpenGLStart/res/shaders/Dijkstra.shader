#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormal;

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Model;
 
out vec3 normal;
out vec3 fragPos;
void main()
{
	gl_Position = u_Projection * u_View *  u_Model * vec4(position, 1.0f);
	fragPos = vec3(u_Model * vec4(position, 1.0f));
	normal = vec3(u_Model * vec4(aNormal, 0.f));
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};



struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

uniform DirLight dirLight;
#define NUM_POINT_LIGHTS 2
uniform PointLight pointLights[NUM_POINT_LIGHTS];

uniform vec3 u_ViewPosition;

in vec3 normal;
in vec3 fragPos;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos);

float near = 0.1;
float far = 500.0;
float Tmp_LinearizeDepthBuffer(float depth)
{
	float z = depth * 2.0 - 1.0;
	return (2 * near * far) / (far + near - z * (far - near));
}
//vec3 CalcSpotLight()
void main()
{
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(u_ViewPosition - fragPos);
	
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	for (int i = 0; i < NUM_POINT_LIGHTS; ++i) {
		result += CalcPointLight(pointLights[i], norm, viewDir, fragPos);
	}

	vec4 fragColor = vec4(result, 1.0f);
	color = fragColor;

	//float depth = Tmp_LinearizeDepthBuffer(gl_FragCoord.z) / far;
	//color = vec4(vec3(depth), 1.0f);
};

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	//diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	//specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	vec3 ambient = material.ambient * light.ambient;
	vec3 diffuse = light.diffuse * (diff * material.diffuse);
	vec3 specular = light.specular * (spec * material.specular);
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
	vec3 lightDir = normalize(light.position - fragPos);
	//diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	//specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	//attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = material.ambient * light.ambient;
	vec3 diffuse = light.diffuse * (diff * material.diffuse);
	vec3 specular = light.specular * (spec * material.specular);

	ambient  *= attenuation;
	diffuse  *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}
