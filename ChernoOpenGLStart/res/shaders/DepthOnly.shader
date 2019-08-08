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
float near = 0.1; //todo uniform
float far = 500.0;
float LinearizeDepthBuffer(float depth)
{
	float z = depth * 2.0 - 1.0;
	return (2 * near * far) / (far + near - z * (far - near));
}
void main()
{
	float depth = LinearizeDepthBuffer(gl_FragCoord.z) / far;
	color = vec4(vec3(depth), 1.0f);
};