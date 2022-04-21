#include <iostream>

#include "imgui.h"

import Application;
import RenderScene;

void menu_example(application* app)
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

int main(int argc, char** argv)
{
    application* app = new application();

    app->push_layer_window<simple_render>();

	app->set_menubar_callback([app]() { menu_example(app); });

    app->run();

	delete app;
}