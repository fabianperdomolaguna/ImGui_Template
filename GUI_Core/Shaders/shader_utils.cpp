module;

#include <string>
#include <fstream>

export module Shaders;

export struct shader
{
	void load(const std::string& vertexshader_file, const std::string& fragmentshader_file)
	{
		std::ifstream is_vs(vertexshader_file);
		const std::string f_vs((std::istreambuf_iterator<char>(is_vs)), std::istreambuf_iterator<char>());

		std::ifstream is_fs(fragmentshader_file);
		const std::string f_fs((std::istreambuf_iterator<char>(is_fs)), std::istreambuf_iterator<char>());
	}
};