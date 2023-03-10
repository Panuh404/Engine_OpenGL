#include "Engine/Renderer/Texture.h"

#include <iostream>
#include <stb_image.h>

namespace Quiet
{
	Texture::Texture(const std::string& path) : m_Path(path)
	{
		glGenTextures(1, &m_RendererID);
	    glBindTexture(GL_TEXTURE_2D, m_RendererID);
	    
	    // Set Texture Wrapping
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	    // Set Texture Filtering
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// load and generate the texture
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true); // Flip texture
	    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	    if (!data) { std::cout << "Failed to load texture" << std::endl; }

	    m_Width = width;
	    m_Height = height;
	    m_Channels = channels;

	    // Switch between RGB and RGBA
	    if (channels == 4)
	    {
	        m_InternalFormat = GL_RGBA8;
	        m_DataFormat = GL_RGBA;
	    }
	    else if (channels == 3)
	    {
	        m_InternalFormat = GL_RGB8;
	        m_DataFormat = GL_RGB;
	    }    

		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, width, height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	    stbi_image_free(data);
	}

	Texture::~Texture()
	{
	    glDeleteTextures(1, &m_RendererID);
	}

	void Texture::Bind(uint32_t slot) const
	{
	    glActiveTexture(GL_TEXTURE0 + slot);
	    glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}