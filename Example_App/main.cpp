#include <iostream>

#include "imgui.h"

import Application;
import RenderScene;
import MainMenu;

int main(int argc, char** argv)
{
	application* app = new application("ImGui - OpenGL Context", 1200, 600);

	app->push_layer_window<simple_render>();

	app->set_menubar_callback([app]() { menu_example(app); });

	app->run();

	delete app;
}