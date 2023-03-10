#pragma once
#include <string>

#include <glad/glad.h>

namespace Quiet
{
	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
		uint32_t GeChannels() const { return m_Channels; }

		void Bind(uint32_t slot = 0) const ;

	private:
		uint32_t m_RendererID;
		std::string m_Path;

		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_Channels;

		GLenum m_InternalFormat;
		GLenum m_DataFormat;
	};
}
