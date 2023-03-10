#include "Engine/Renderer/Shader.h"
#include <fstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Quiet
{
	Shader::Shader(const std::string name, const std::string& vertexSource, const std::string& fragmentSource) : m_Name(name)
	{
		std::string vShaderCode = ReadFile(vertexSource);
		std::string fShaderCode = ReadFile(fragmentSource);

		const char* vertexFile = vShaderCode.c_str();
		const char* fragmentFile = fShaderCode.c_str();

		// Vertex Shader
		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexFile, nullptr);
		glCompileShader(vertexShader);
		verify(vertexShader, VERTEX_SHADER);

		// Fragment Shader
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentFile, nullptr);
		glCompileShader(fragmentShader);
		verify(fragmentShader, FRAGMENT_SHADER);

		// Shader Program
		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		glLinkProgram(m_RendererID);
		verify(m_RendererID, PROGRAM_SHADER);

		// Cleanup
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	std::string Shader::ReadFile(std::string filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else std::cout << "LOAD FILE::Could not open file {0}" << filepath << std::endl;
		}
		else std::cout << "LOAD FILE::Could not open file {0}" << filepath << std::endl;
		return result;
	}

	void Shader::verify(uint32_t shader, ShaderType type)
	{
		if (type == VERTEX_SHADER)
		{
			int success;
			char infoLog[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(shader, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
		}

		if (type == FRAGMENT_SHADER)
		{
			int success;
			char infoLog[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(shader, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
		}

		if (type == PROGRAM_SHADER)
		{
			int success;
			char infoLog[512];
			glGetShaderiv(shader, GL_LINK_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(shader, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
			}
		}
	}

	void Shader::SetInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void Shader::SetIntArr(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void Shader::SetFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void Shader::SetFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void Shader::SetFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void Shader::SetFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void Shader::SetMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}