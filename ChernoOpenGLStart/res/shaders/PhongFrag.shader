//#version 330 core

#ifndef HAS_TEXCOORD
	#define HAS_TEXCOORD 0
#endif
#ifndef HAS_DIFFUSE_TEXTURE
	#define HAS_DIFFUSE_TEXTURE 0
#endif
#ifndef SHADOW_PASS
	#define SHADOW_PASS 0
#endif


layout(location = 0) out vec4 color;


#if !SHADOW_PASS
uniform sampler2D shadowMap;
#endif
#if HAS_DIFFUSE_TEXTURE
uniform sampler2D texDiffuse;
#endif

struct DirLight {
	vec3 direction;

	//vec3 ambient;
	//vec3 diffuse;
	//vec3 specular;
};


#if !HAS_DIFFUSE_TEXTURE
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;
#endif
uniform DirLight u_DirLight;

uniform vec3 u_ViewPosition;

in vec3 normal;
in vec3 fragPos;
#if HAS_TEXCOORD
in vec2 tCoord;
#endif
#if !SHADOW_PASS
in vec4 fragPosLightSpace;
#endif


#if !SHADOW_PASS

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, float shadow)
{
	vec3 lightDir = normalize(-light.direction);
	//diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	//specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec;
#if HAS_DIFFUSE_TEXTURE
	spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.f);
#else
	spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
#endif

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

#if HAS_DIFFUSE_TEXTURE
	ambient = texture(texDiffuse, tCoord).rgb * 0.2f;
	diffuse = diff * texture(texDiffuse, tCoord).rgb * 0.8f;
	specular = spec * vec3(0.5f, 0.5f, 0.5f) * 0.0f;
	return (ambient + (1 - shadow) * (diffuse + specular));
#else
	//vec3 ambient = material.ambient * light.ambient;
	//vec3 diffuse = light.diffuse * (diff * material.diffuse);
	//vec3 specular = light.specular * (spec * material.specular);
	ambient = material.ambient * 0.1f;
	diffuse = diff * material.diffuse * 0.5;
	specular = spec * material.specular * 1.2f;
	return (ambient + (1 - shadow) * ( diffuse + specular ));
#endif
}

float CalculateShadow(vec4 PosLightSpace)
{
	float shadow_bias = 0.005f;
	//from clip-space to NDC;
	vec3 shadow_uv = PosLightSpace.xyz  / PosLightSpace.w;
	//from NDC to range [0;1]	
	shadow_uv = shadow_uv * 0.5f +0.5f;
	float shadowMapDepth = texture(shadowMap, shadow_uv.xy).r;
	float currentDepth = shadow_uv.z - shadow_bias;
	float shadow = currentDepth > shadowMapDepth ? 1.0f : 0.f;
	return shadow;
}
#endif

void main()
{
#if SHADOW_PASS
	//just write to depth
	return;
#else
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(u_ViewPosition - fragPos);

	float shadow = CalculateShadow(fragPosLightSpace);
	vec3 result = CalcDirLight(u_DirLight, norm, viewDir, shadow);

	vec4 fragColor = vec4(result, 1.0f);
	color = fragColor;

	//float depth = Tmp_LinearizeDepthBuffer(gl_FragCoord.z) / far;
	//color = vec4(vec3(depth), 1.0f);
#endif
};

