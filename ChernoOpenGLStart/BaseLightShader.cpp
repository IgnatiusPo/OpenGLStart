#include "BaseLightShader.h"



BaseLightShader::BaseLightShader(const std::string& filepath) : Shader(filepath)
{

}


void BaseLightShader::SetPointLightPositions(glm::vec3* pointLightPositions)
{
	_pointLightPositions = pointLightPositions;
}
void BaseLightShader::PrepareForDraw()
{
	//material	
	SetUniform3f("material.ambient", 1.0f, 0.5f, 0.31f);
	SetUniform3f("material.diffuse", 1.0f, 0.5f, 0.31f);
	SetUniform3f("material.specular", 0.2f, 0.2f, 0.2f);
	SetUniform1f("material.shininess", 32);

	//directional light
	SetUniform3f("dirLight.direction", -0.2f, -1.f, 0.3f);
	SetUniform3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	SetUniform3f("dirLight.diffuse", .3f, .3f, .3f);
	SetUniform3f("dirLight.specular", .5f, .5f, .5f);

	//point lights
	if (!_pointLightPositions)
		return;

	SetUniform3f("pointLights[0].position", _pointLightPositions[0]);
	SetUniform3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	SetUniform3f("pointLights[0].diffuse", 1.f, 1.f, 1.f);
	SetUniform3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	SetUniform1f("pointLights[0].constant", 1.0f);
	SetUniform1f("pointLights[0].linear", 0.014f);
	SetUniform1f("pointLights[0].quadratic", 0.0007f);

	SetUniform3f("pointLights[1].position", _pointLightPositions[1]);
	SetUniform3f("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	SetUniform3f("pointLights[1].diffuse", 0.f, 3.f, 2.f);
	SetUniform3f("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	SetUniform1f("pointLights[1].constant", 1.0f);
	SetUniform1f("pointLights[1].linear", 0.09);
	SetUniform1f("pointLights[1].quadratic", 0.032f);
}

void BaseLightShader::UpdateModelMatrix(const glm::mat4& model)
{
	SetUniformMat4f("u_Model", model);
}
void BaseLightShader::UpdateViewMatrix(const glm::mat4& view)
{
	SetUniformMat4f("u_View", view);
}
void BaseLightShader::UpdateProjectionMatrix(const glm::mat4& projection)
{
	SetUniformMat4f("u_Projection", projection);
}
void BaseLightShader::UpdateuViewPositionMatrix(const glm::vec3& viewPos)
{
	SetUniform3f("u_ViewPosition", viewPos);
}
BaseLightShader::~BaseLightShader()
{
}
