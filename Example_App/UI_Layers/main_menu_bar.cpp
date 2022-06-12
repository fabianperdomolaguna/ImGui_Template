module;

#include <fstream>
#include <string>

#include "imgui.h"
#include "nlohmann/json.hpp"

export module MainMenu;

import Application;

struct menu_variables
{
	bool exit_item = false;
	bool theme_item = false;
};

void exit_popup(bool &exit_item, application *app)
{
	if (exit_item)
		ImGui::OpenPopup("Close the application?");

	// Always center this window when appearing
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (ImGui::BeginPopupModal("Close the application?", NULL, ImGuiWindowFlags_NoResize))
	{
		ImGui::Text("Are you sure to close the application?\nActive edits will not be saved!\n\n");
		ImGui::Separator();

		if (ImGui::Button("Ok", ImVec2(120, 0)))
			app->window_app->m_running = false;
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0)))
			ImGui::CloseCurrentPopup();
			
		ImGui::EndPopup();
	}
}

void change_style_popup(bool &theme_item, application* app)
{
	if (theme_item)
		ImGui::OpenPopup("App color theme");

	// Always center this window when appearing
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (ImGui::BeginPopupModal("App color theme", NULL, ImGuiWindowFlags_NoResize))
	{
		ImGui::Text("Close the app to aply theme changes.\n");
		ImGui::Separator();

		if (ImGui::Button("Ok", ImVec2(120, 0)))
			ImGui::CloseCurrentPopup();

		ImGui::EndPopup();
	}

}

void change_app_style(std::string app_style)
{
	std::fstream json_config_file;
	json_config_file.open("ConfigFile.json", std::ios::in);
	nlohmann::json json_data = nlohmann::json::parse(json_config_file);
	json_config_file.close();

	json_data["GuiStyle"] = app_style;

	json_config_file.open("ConfigFile.json", std::ios::out);
	json_config_file << json_data;
	json_config_file.close();
}

export void menu_example(application* app)
{
	menu_variables m_variables;

	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Exit"))
			m_variables.exit_item = true;

		if (ImGui::BeginMenu("Color Theme"))
		{
			if (ImGui::MenuItem("Dark", ""))
			{
				change_app_style("dark");
				m_variables.theme_item = true;
			}

			if (ImGui::MenuItem("Light", ""))
			{
				change_app_style("light");
				m_variables.theme_item = true;
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenu();
	}

	exit_popup(m_variables.exit_item, app);
	change_style_popup(m_variables.theme_item, app);
};