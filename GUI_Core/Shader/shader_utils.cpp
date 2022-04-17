module;

#include <iostream>
#include <string>
#include <fstream>

#include "glad/glad.h"

export module Shaders;

export struct shader
{
	uint32_t shader_program = 0;

	shader() { gladLoadGL(); }

	~shader() { unload(); }

	uint32_t compile(unsigned int shader_type, const std::string& shader_source)
	{
		uint32_t shader_id = glCreateShader(shader_type);

		const char* c_source = shader_source.c_str();
		glShaderSource(shader_id, 1, &c_source, nullptr);
		glCompileShader(shader_id);

		int32_t result;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			int32_t length;
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);

			GLchar* strInfoLog = new GLchar[length + 1];
			glGetShaderInfoLog(shader_id, length, &length, strInfoLog);
			std::cout << "Failed to compile " << (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
			std::cout << "Compile error: " << strInfoLog << std::endl;
			delete[] strInfoLog;
			glDeleteShader(shader_id);
			return 0;
		}

		return shader_id;
	}

	void create(const std::string& vertexshader_file, const std::string& fragmentshader_file)
	{
		std::ifstream is_vs(vertexshader_file);
		const std::string f_vs((std::istreambuf_iterator<char>(is_vs)), std::istreambuf_iterator<char>());

		std::ifstream is_fs(fragmentshader_file);
		const std::string f_fs((std::istreambuf_iterator<char>(is_fs)), std::istreambuf_iterator<char>());

		shader_program = glCreateProgram();

		uint32_t vs = compile(GL_VERTEX_SHADER, f_vs);
		uint32_t fs = compile(GL_FRAGMENT_SHADER, f_fs);

		glAttachShader(shader_program, vs);
		glAttachShader(shader_program, fs);
		glLinkProgram(shader_program);
		glValidateProgram(shader_program);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	void use()
	{
		glUseProgram(shader_program);
	}

	void unload()
	{
		glDeleteProgram(shader_program);
	}
};