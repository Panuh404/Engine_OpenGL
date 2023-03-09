#pragma once
#include <string>
#include <unordered_map>
#include <glad/glad.h>

enum ShaderType
{
	VERTEX_SHADER,
	FRAGMENT_SHADER,
	PROGRAM_SHADER
};

class Shader
{
public:
	Shader(std::string name, const std::string& vertexSource, const std::string& fragmentSource);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Uniforms Handle
	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);

private:
	uint32_t m_RendererID;
	std::string m_Name;

	std::string ReadFile(std::string filepath);
	void verify(uint32_t shader, ShaderType type);
};
