#include <iostream>

#include "imgui.h"

import Application;
import RenderScene;

void menu_example()
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Exit")) {}
		if (ImGui::MenuItem("Cut", "CTRL+X")) {}
		ImGui::EndMenu();
	}
};

int main(int argc, char** argv)
{
    application* app = new application();

    app->push_layer<simple_render>();

	app->set_menubar_callback([app]() { menu_example(); });

    app->run();

	delete app;
}