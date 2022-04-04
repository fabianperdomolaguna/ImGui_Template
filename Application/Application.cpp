#include "GLFW/glfw3.h"
#include <iostream>

import Window;
import ImGuiLayer;
import EditorLayer;

int main(int argc, char** argv) 
{
    //std::unique_ptr<window> Window(new window());
    window* Window = new window();
    ImGuiLayer::attach(Window->m_window);

    while (Window->m_data.m_running)
    {
        //glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        //glClear(GL_COLOR_BUFFER_BIT);

        ImGuiLayer::begin();
        EditorLayer::editor();
        ImGuiLayer::end();

        glfwSwapBuffers(Window->m_window);
        glfwPollEvents();
    }

    ImGuiLayer::detach();

    glfwTerminate();
    delete Window;
}