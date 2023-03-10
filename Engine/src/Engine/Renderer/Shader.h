#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Quiet
{
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
		void SetIntArr(const std::string& name, int* values, uint32_t count);
		void SetFloat(const std::string& name, float value);
		void SetFloat2(const std::string& name, const glm::vec2& values);
		void SetFloat3(const std::string& name, const glm::vec3& values);
		void SetFloat4(const std::string& name, const glm::vec4& values);
		void SetMat3(const std::string& name, const glm::mat3& matrix);
		void SetMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;
		std::string m_Name;

		std::string ReadFile(std::string filepath);
		void verify(uint32_t shader, ShaderType type);
	};
}