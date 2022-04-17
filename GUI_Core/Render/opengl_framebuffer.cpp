module;

#include <iostream>

#include "glad/glad.h"

export module OpenGLFramebuffers;

export struct opengl_framebuffer
{
	uint32_t FBO = 0;
	uint32_t RBO = 0;
	uint32_t render_texture = 0;
	int32_t m_width;
	int32_t m_height;

	opengl_framebuffer(int32_t width, int32_t height) 
	{ 
		gladLoadGL();
		create_buffers(width, height);
	}

	~opengl_framebuffer() { delete_buffers(); }

	void create_buffers(int32_t width, int32_t height)
	{
		m_width = width;
		m_height = height;

		if (FBO)
			delete_buffers();

		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		glGenTextures(1, &render_texture);
		glBindTexture(GL_TEXTURE_2D, render_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, render_texture, 0);

		glGenRenderbuffers(1, &RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void delete_buffers()
	{
		glDeleteFramebuffers(GL_FRAMEBUFFER, &FBO);
		glDeleteRenderbuffers(1, &RBO);
		glDeleteTextures(1, &render_texture);
	}

	void bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glViewport(0, 0, m_width, m_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32_t get_texture()
	{
		return render_texture;
	}
};