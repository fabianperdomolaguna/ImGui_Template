module;

#include "imgui.h"

export module MainMenu;

import Application;

export void menu_example(application* app)
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Exit"))
		{
			app->window_app->m_running = false;
		}
		if (ImGui::MenuItem("Cut", "CTRL+X")) {}
		ImGui::EndMenu();
	}
};