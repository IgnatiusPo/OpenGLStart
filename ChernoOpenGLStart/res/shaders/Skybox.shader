#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

out vec3 TexCoords;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	TexCoords = position;
	mat4 view = mat4(mat3(u_View));
	vec4 pos = u_Projection * view * vec4(position, 1.0);
	gl_Position = pos.xyww; //set z = 1.0 to simulate the farest depth location
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{
	FragColor = texture(skybox, TexCoords);
}