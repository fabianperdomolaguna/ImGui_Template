#include <iostream>

#include "GLFW/glfw3.h"
#include "imgui.h"

import Window;
import ImguiContext;
import OpenGLVertex;
import EditorLayer;

int main(int argc, char** argv)
{
    auto window_app = std::make_unique<gl_window>();
    auto imgui_context = std::make_unique<ui_context>(window_app->m_window);
    auto vertex_draw = std::make_unique<opengl_vertex>("Shaders_Files/vs.shader", "Shaders_Files/fs.shader");

    vertex_draw->create_buffers();

    float m_sizex;
    float m_sizey;

    while (window_app->m_running)
    {
        window_app->pre_render();

        imgui_context->pre_render();

        window_app->m_framebuffer->bind();
        vertex_draw->draw();
        window_app->m_framebuffer->unbind();

        ImGui::Begin("Scene");

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_sizex = viewportPanelSize.x;
        m_sizey = viewportPanelSize.y;

        // add rendered texture to ImGUI scene window
        uint64_t textureID = window_app->m_framebuffer->get_texture();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_sizex, m_sizey }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        ImGui::End();

        EditorLayer::prueba();

        imgui_context->post_render();

        window_app->post_render();
    }

}