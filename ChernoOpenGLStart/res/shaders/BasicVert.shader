//#version 330 core

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