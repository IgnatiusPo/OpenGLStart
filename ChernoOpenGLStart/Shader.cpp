#include <GL/glew.h>
#include "Shader.h"
//#include "Renderer.h"
#include "Macroses.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"




Shader::Shader(const std::string& vertShader, const std::string& fragShader) : _vertShader(vertShader), _fragShader(fragShader), _RendererID(0)
{
	//ShaderProgramSource source = ParseShader(filepath);
	//_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
	
	_RendererID = CreateShader(vertShader, fragShader);
}

Shader::~Shader()
{
	//GLCall(glDeleteProgram(_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));

}


void Shader::SetUniform(const std::string& name, const int& value)
{
	GLCall(glUniform1i(GetUniformLocation(name),value));

}

void Shader::SetUniform(const std::string& name, const float& v0, const float& v1, const float& v2, const float& v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0,  v1, v2, v3));
}

void Shader::SetUniform(const std::string& name, const glm::vec4& uniform)
{
	GLCall(glUniform4f(GetUniformLocation(name), uniform.x, uniform.y, uniform.z, uniform.w));
}

void Shader::SetUniform(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniform(const std::string& name, const float& v0, const float& v1, const float& v2)
{
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform(const std::string& name, const glm::vec3& uniform)
{
	GLCall(glUniform3f(GetUniformLocation(name), uniform.x, uniform.y, uniform.z));
}

void Shader::SetUniform(const std::string& name, const float& value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform(const std::string& name, const glm::vec1& uniform)
{
	GLCall(glUniform1f(GetUniformLocation(name), uniform.x));
}

void Shader::SetUniform(const std::string& name, const glm::vec2& uniform)
{
	GLCall(glUniform2f(GetUniformLocation(name), uniform.x, uniform.y));
}

void Shader::SetUniform(const std::string& name, const glm::ivec1& uniform)
{
	GLCall(glUniform1i(GetUniformLocation(name), uniform.x));

}

void Shader::SetUniform(const std::string& name, const glm::ivec2& uniform)
{
	GLCall(glUniform2i(GetUniformLocation(name), uniform.x, uniform.y));

}

void Shader::SetUniform(const std::string& name, const glm::ivec3& uniform)
{
	GLCall(glUniform3i(GetUniformLocation(name), uniform.x, uniform.y, uniform.z));

}

void Shader::SetUniform(const std::string& name, const glm::ivec4& uniform)
{
	GLCall(glUniform4i(GetUniformLocation(name), uniform.x, uniform.y, uniform.z, uniform.w));

}

void Shader::SetUniform(const std::string& name, const glm::mat3& uniform)
{
	GLCall(glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE,  &uniform[0][0]));
}

void Shader::SetUniform(const std::string& name, TextureUniform tex)
{
	Texture* texture = Renderer::GetTextureByID(tex.textureID);
	SetUniform(name, glm::ivec1((unsigned int)tex.textureClass));
	texture->Bind((unsigned int)tex.textureClass);
}

void Shader::SetUniform(const Uniform& uniform)
{
	UniformType Type = uniform.type;
	switch (Type)
	{
	case UniformType::mat3: {
		SetUniform(uniform.name, uniform.m3);
		break;
	}
	case UniformType::mat4: {
		SetUniform(uniform.name, uniform.m4);
		break;
	}
	case UniformType::vec1f: {
		SetUniform(uniform.name, uniform.v1);
		break;
	}
	case UniformType::vec2f: {
		SetUniform(uniform.name, uniform.v2);
		break;
	}
	case UniformType::vec3f: {
		SetUniform(uniform.name, uniform.v3);
		break;
	}
	case UniformType::vec4f: {
		SetUniform(uniform.name, uniform.v4);
		break;
	}
	case UniformType::vec1i: {
		SetUniform(uniform.name, uniform.iv1);
		break;
	}
	case UniformType::vec2i: {
		SetUniform(uniform.name, uniform.iv2);
		break;
	}
	case UniformType::vec3i: {
		SetUniform(uniform.name, uniform.iv3);
		break;
	}
	case UniformType::vec4i: {
		SetUniform(uniform.name, uniform.iv4);
		break;
	}
	case UniformType::tex: {
		SetUniform(uniform.name, uniform.tex);
	}
	}
}


std::string Shader::ParseShader(const std::string& filepath)
{
	std::string source;
	std::string tmp;
	std::ifstream stream(filepath);
		
	if (!stream.is_open() || stream.bad())
	{
		std::cerr << "Error: Problems while reading: " << filepath << std::endl;
		__debugbreak();
	}

	if (!getline(stream, tmp))
	{
		std::cerr << "Error: Problems while reading: " << filepath << std::endl;
		__debugbreak();
	}
	else
	{
		source += tmp + '\n';
	}

	while (getline(stream, tmp))
	{
		source += tmp + '\n';
	}
	return source;
}

//ShaderProgramSource Shader::ParseShader(const std::string& filepath)
//{
//	std::ifstream stream(filepath);
//
//	enum class ShaderType
//	{
//		NONE = -1, VERTEX = 0, FRAGMENT = 1
//	};
//
//	std::string line;
//	std::stringstream ss[2];
//	ShaderType type = ShaderType::NONE;
//	while (getline(stream, line))
//	{
//		if (line.find("#shader") != std::string::npos)
//		{
//			if (line.find("vertex") != std::string::npos)
//			{
//				type = ShaderType::VERTEX;
//			}
//			else if (line.find("fragment") != std::string::npos)
//			{
//				type = ShaderType::FRAGMENT;
//			}
//		}
//		else
//		{
//			ss[(int)type] << line << '\n';
//		}
//	}
//
//	return { ss[0].str(), ss[1].str() };
//}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* message = (char*)alloca(lenght * sizeof(char));

		glGetShaderInfoLog(id, lenght, &lenght, message);
		std::cerr << "failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cerr << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}



int Shader::GetUniformLocation(const std::string& name)
{
	if (_UniformLocationCache.find(name) != _UniformLocationCache.end())
		return _UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(_RendererID, name.c_str()));
	if (location == -1)
	{
		//todo
		//std::cerr << "Warning: uniform" << name << " doesn't exist! " << std::endl;
	}
	else
		_UniformLocationCache.insert(std::make_pair(name, location));
		//_UniformLocationCache[name] = location; 
	return location;
}


//Shader* Shader::GetDepthOnlyShader()
//{
//	static Shader shaderObject("res/shaders/DepthOnly.shader");
//	return &shaderObject;
//}

//void Shader::PrepareForDraw()
//{
//	//no work needed to be done for Base Shader		
//}
