//#version 330 core

#ifndef HAS_TEXCOORD
	#define HAS_TEXCOORD 0
#endif

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormal;
#if HAS_TEXCOORD
layout(location = 2) in vec2 texCoord;
#endif

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Model;
#if !SHADOW_PASS
//todo 1 matrix
uniform mat4 u_LightView;
uniform mat4 u_LightProjection;
#endif


out vec3 normal;
out vec3 fragPos;
#if HAS_TEXCOORD
out vec2 tCoord;
#endif
#if !SHADOW_PASS
out vec4 fragPosLightSpace;
#endif
void main()
{
	gl_Position = u_Projection * u_View *  u_Model * vec4(position, 1.0f);
	fragPos = vec3(u_Model * vec4(position, 1.0f));
	normal = vec3(u_Model * vec4(aNormal, 0.f));
#if HAS_TEXCOORD
	tCoord = texCoord;
#endif
#if !SHADOW_PASS
	fragPosLightSpace = u_LightProjection * u_LightView * u_Model * vec4(position, 1.0f);
#endif
};