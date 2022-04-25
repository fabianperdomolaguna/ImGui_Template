module;

#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glad/glad.h"

export module Image;

export struct image
{
	std::string m_filepath;
	uint32_t m_width = 0, m_height = 0;
	uint32_t image_texture;
	uint32_t m_format = 0;

	image(std::string file_path): m_filepath(file_path)
	{
		gladLoadGL();

		int width, height, channels;
		uint8_t* data = nullptr;

		if (stbi_is_hdr(m_filepath.c_str()))
		{
			data = (uint8_t*)stbi_loadf(m_filepath.c_str(), &width, &height, &channels, 4);
			m_format = GL_RGBA32F;
		}
		else
		{
			data = stbi_load(m_filepath.c_str(), &width, &height, &channels, 4);
			m_format = GL_RGBA;
		}

		m_width = width;
		m_height = height;

		glGenTextures(1, &image_texture);
		glBindTexture(GL_TEXTURE_2D, image_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	~image() 
	{
		glDeleteTextures(1, &image_texture);
	}

	uint32_t get_texture()
	{
		return image_texture;
	}
};