module;

#include <iostream>

#include "glad/glad.h"

export module OpenGLVertex;

import Shaders;

float vertices[] = {
			-0.5f, -0.5f, 0.0f, // left  
			 0.5f, -0.5f, 0.0f, // right 
			 0.0f,  0.5f, 0.0f  // top   
};

export struct opengl_vertex
{
	uint32_t VAO = 0;
	uint32_t VBO = 0;

	std::unique_ptr<shader> m_shader;

	opengl_vertex(std::string vertexshader, std::string fragmentshader)
	{ 
		gladLoadGL(); 
		m_shader = std::make_unique<shader>();
		m_shader->create(vertexshader, fragmentshader);
	}

	~opengl_vertex()
	{
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void create_buffers()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void bind()
	{
		glBindVertexArray(VAO);
	}

	void unbind()
	{
		glBindVertexArray(0);
	}

	void draw()
	{
		bind();

		glClearColor(0.02f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		m_shader->use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		unbind();
	}

};