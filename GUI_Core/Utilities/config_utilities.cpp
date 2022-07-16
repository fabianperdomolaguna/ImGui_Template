module;

#include <fstream>
#include <string>

#include "nlohmann/json.hpp"

export module ConfigUtilities;

export
{
	std::string get_config_variable(std::string config_variable)
	{
		std::fstream json_config_file;
		json_config_file.open("ConfigFile.json", std::ios::in);
		nlohmann::json json_data = nlohmann::json::parse(json_config_file);
		json_config_file.close();
		return json_data[config_variable].get<std::string>();
	}

	void change_config_variable(std::string config_variable, std::string new_value)
	{
		std::fstream json_config_file;
		json_config_file.open("ConfigFile.json", std::ios::in);
		nlohmann::json json_data = nlohmann::json::parse(json_config_file);
		json_config_file.close();

		json_data[config_variable] = new_value;

		json_config_file.open("ConfigFile.json", std::ios::out);
		json_config_file << json_data;
		json_config_file.close();
	}
}