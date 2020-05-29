//#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 u_Model;
uniform mat4 u_Projection;
uniform mat4 u_View;
void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
	//gl_Position =  vec4(position, 1.0);
}