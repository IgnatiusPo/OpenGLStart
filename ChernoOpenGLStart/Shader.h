#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include "Uniform.h"
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
	void SetUniform(const std::string& name, const int& value);
	void SetUniform(const std::string& name, const float& value);
	void SetUniform(const std::string& name, const glm::vec1& uniform);
	void SetUniform(const std::string& name, const glm::vec2& uniform);
	void SetUniform(const std::string& name, const glm::vec3& uniform);
	void SetUniform(const std::string& name, const float& v0, const float& v1, const float& v2);
	void SetUniform(const std::string& name, const glm::vec4& uniform);
	void SetUniform(const std::string& name, const float& v0, const float& v1, const float& v2, const float& v3);
	void SetUniform(const std::string& name, const glm::ivec1& uniform);
	void SetUniform(const std::string& name, const glm::ivec2& uniform);
	void SetUniform(const std::string& name, const glm::ivec3& uniform);
	void SetUniform(const std::string& name, const glm::ivec4& uniform);
	void SetUniform(const std::string& name, const glm::mat4& matrix);
	void SetUniform(const std::string& name, const glm::mat3& uniform);
	

	void SetUniform(const Uniform& uniform);


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

