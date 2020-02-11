#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
private:
	std::string _vertPath;
	std::string _fragPath;
	unsigned int _RendererID;
	std::unordered_map<std::string, int> _UniformLocationCache;

public:
	Shader(const std::string& vertPath, const std::string& fragPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform(const std::string& name, int value);
	void SetUniform(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform(const std::string& name, glm::vec4 uniform);
	void SetUniform(const std::string& name, const glm::mat4 matrix);
	void SetUniform(const std::string& name, float v0, float v1, float v2);
	void SetUniform(const std::string& name, glm::vec3 uniform);
	void SetUniform(const std::string& name, float value);


public:
//	static Shader* GetDepthOnlyShader();
	//virtual void PrepareForDraw();
private:
	//ShaderProgramSource ParseShader(const std::string& filepath);
	std::string ParseShader(const std::string& filepath);

	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int			GetUniformLocation(const std::string& name);
};

