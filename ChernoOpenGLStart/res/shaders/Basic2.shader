#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 u_Transform;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;


void main()
{
	gl_Position = u_Projection * u_View * u_Model * u_Transform * position;
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;


void main()
{
	vec4 texColor = mix(texture(u_Texture1, v_TexCoord), texture(u_Texture2, v_TexCoord), 0.15);
	color = texColor;
};

