#version 330 core

layout(location = 0) out vec4 color;

struct DirLight {
	vec3 direction;

	//vec3 ambient;
	//vec3 diffuse;
	//vec3 specular;
};



struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

uniform DirLight dirLight;

uniform vec3 u_ViewPosition;

in vec3 normal;
in vec3 fragPos;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);


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

	//vec3 ambient = material.ambient * light.ambient;
	//vec3 diffuse = light.diffuse * (diff * material.diffuse);
	//vec3 specular = light.specular * (spec * material.specular);
	vec3 ambient = material.ambient * 0.1f;
	vec3 diffuse = diff * material.diffuse * 0.5;
	vec3 specular = spec * material.specular * 1.2f;
	return (ambient + diffuse + specular);
}
