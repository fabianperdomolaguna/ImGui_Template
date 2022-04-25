module;

#include <iostream>

#include "imgui.h"

export module RenderScene;

import Window;
import Layer;
import OpenGLVertex;
import OpenGLFramebuffers;
import Image;

export struct simple_render : public layer
{
    std::unique_ptr<opengl_vertex> vertex_draw;
    std::unique_ptr<opengl_framebuffer> m_framebuffer;

    std::shared_ptr<image> m_image;

    simple_render(std::unique_ptr<gl_window> &window)
    {
        vertex_draw = std::make_unique<opengl_vertex>("Shaders_Files/vs.shader", "Shaders_Files/fs.shader");
        m_framebuffer = std::make_unique<opengl_framebuffer>(window->m_width, window->m_height);
        vertex_draw->create_buffers();
    }

    virtual void on_attach() override
    {
        m_image = std::make_shared<image>("go_logo.jpg");
    }

    virtual void on_ui_render() override
    {
        m_framebuffer->bind();
        vertex_draw->draw();
        m_framebuffer->unbind();

        ImGui::Begin("Scene");
        // add rendered texture to ImGUI scene window
        uint64_t textureID = m_framebuffer->get_texture();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImGui::GetContentRegionAvail(), ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        ImGui::End();

        ImGui::Begin("Image OpenGl Texture");
        ImGui::Image(reinterpret_cast<void*>((uint64_t)m_image->get_texture()), { (float)m_image->m_width, (float)m_image->m_height});
        ImGui::End();

        ImGui::ShowDemoWindow();
    }
};