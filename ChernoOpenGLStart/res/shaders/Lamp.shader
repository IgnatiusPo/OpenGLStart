#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Projection * u_View *  u_Model * position, 1.0f;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_LampColor;

void main()
{
	vec4 texColor = u_LampColor;
	color = texColor;
};

