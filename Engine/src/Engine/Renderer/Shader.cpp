#include "Shader.h"
#include <fstream>
#include <iostream>

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
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
		else
		{
			std::cout << "SHADER::VERTEX::COMPILED" << std::endl;
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
		else
		{
			std::cout << "SHADER::FRAGMENT::COMPILED" << std::endl;
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
		else
		{
			std::cout << "SHADER::LINKED" << std::endl;
		}
	}
}