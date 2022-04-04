module;

#include <iostream>
#include <string>
#include "GLFW/glfw3.h"
#include <windows.h>

export module Window;

import ImGuiLayer;

struct WindowData
{
    bool m_running = true;
    std::string title = "Segy - C++20";
    uint16_t width = 1200;
    uint16_t height = 600;
};

export struct window 
{
    GLFWwindow* m_window;
    WindowData m_data;

    window()
    {
        if (!glfwInit())
            std::cerr << "Could not intialize GLFW!";

        m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), NULL, NULL);
        glfwMakeContextCurrent(m_window);

        if (!m_window)
        {
            glfwTerminate();
            std::cerr << "Could not intialize a window!";
        }

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            int message = MessageBox(NULL, L"Are you sure to close the program?", L"Close window!", MB_OKCANCEL | MB_ICONQUESTION);
            if (message == IDOK)
                data.m_running = true;
        });
    }

    ~window() {}
};