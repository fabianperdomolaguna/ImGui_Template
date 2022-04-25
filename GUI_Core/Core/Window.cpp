module;

#include <iostream>
#include <string>
#include <windows.h>

#include "GLFW/glfw3.h"

export module Window;

export struct gl_window
{
    GLFWwindow* m_window;
    bool m_running = true;

    std::string title;
    int32_t m_width;
    int32_t m_height;

    gl_window(std::string& window_title, int32_t& width, int32_t& height)
    {
        title = window_title;
        m_width = width;
        m_height = height;

        if (!glfwInit())
        {
            std::cout << "Could not intialize GLFW!\n";
            m_running = false;
        }

        m_window = glfwCreateWindow(m_width, m_height, window_title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);

        if (!m_window)
        {
            std::cout << "Could not intialize a window!\n";
            m_running = false;
        }

        glfwSetWindowUserPointer(m_window, this);

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
        {
            gl_window& window_app = *(gl_window*)glfwGetWindowUserPointer(window);
            int message = MessageBox(NULL, L"Are you sure to close the program?", L"Close window!", MB_OKCANCEL | MB_ICONQUESTION);
            if (message == IDOK)
                window_app.m_running = false;
        });

        glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
        {
            gl_window& window_app = *(gl_window*)glfwGetWindowUserPointer(window);
            window_app.m_width = width;
            window_app.m_height = height;
        });

        glEnable(GL_DEPTH_TEST);
    }

    ~gl_window()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void pre_render()
    {
        glViewport(0, 0, m_width, m_height);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void post_render()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }
};