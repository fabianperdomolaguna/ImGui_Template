module;

#include <iostream>
#include <vector>
#include <functional>

#include "imgui.h"

export module Application;

import Window;
import ImguiContext;
import Layer;

export struct application
{
	std::unique_ptr<gl_window> window_app;
	std::unique_ptr<ui_context> imgui_context;

	std::vector<std::shared_ptr<layer>> m_layerstack;

	std::function<void()> m_menubar_callback;

	application(std::string window_title, int32_t width, int32_t height)
	{
		window_app = std::make_unique<gl_window>(window_title, width, height);
		imgui_context = std::make_unique<ui_context>(window_app->m_window);
	}

	~application() {}

	void run()
	{
		while (window_app->m_running)
		{
			window_app->pre_render();
			imgui_context->pre_render(m_menubar_callback != 0);

			if (m_menubar_callback)
			{
				if (ImGui::BeginMainMenuBar())
				{
					m_menubar_callback();
					ImGui::EndMainMenuBar();
				}
			}

			for (auto& layer_render : m_layerstack)
				layer_render->on_ui_render();

			imgui_context->post_render();
			window_app->post_render();
		}
	}

	template<typename T>
	void push_layer()
	{
		static_assert(std::is_base_of<layer, T>::value, "Pushed type is not subclass of Layer!");
		m_layerstack.emplace_back(std::make_shared<T>())->on_attach();
	}

	template<typename T>
	void push_layer_window()
	{
		static_assert(std::is_base_of<layer, T>::value, "Pushed type is not subclass of Layer!");
		m_layerstack.emplace_back(std::make_shared<T>(window_app))->on_attach();
	}

	void set_menubar_callback(const std::function<void()>& menubar_callback) { m_menubar_callback = menubar_callback; }
};