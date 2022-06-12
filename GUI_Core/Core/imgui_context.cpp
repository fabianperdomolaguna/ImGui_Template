module;

#include <string>
#include <fstream>
#include <unordered_map>
#include <any>

#include "GLFW/glfw3.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "nlohmann/json.hpp"

#include "Fonts/Roboto_Regular.h"
#include "Fonts/Roboto_Bold.h"
#include "Fonts/Roboto_Italic.h"

export module ImguiContext;

void set_dark_theme_colors()
{
    constexpr auto color_from_bytes = [](uint8_t r, uint8_t g, uint8_t b)
    {
        return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
    };

    auto& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    const ImVec4 bg_color = color_from_bytes(37, 37, 38);
    const ImVec4 light_bg_color = color_from_bytes(82, 82, 85);
    const ImVec4 very_light_bg_color = color_from_bytes(90, 90, 95);

    const ImVec4 panel_color = color_from_bytes(65, 65, 70);
    const ImVec4 panel_hover_color = color_from_bytes(29, 151, 236);
    const ImVec4 panel_active_color = color_from_bytes(0, 119, 200);

    const ImVec4 text_color = color_from_bytes(255, 255, 255);
    const ImVec4 text_disabled_color = color_from_bytes(151, 151, 151);
    const ImVec4 border_color = color_from_bytes(78, 78, 78);

    const ImVec4 check_color = color_from_bytes(255, 153, 0);


    colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.1f, 0.1f, 1.0f };
    colors[ImGuiCol_ChildBg] = bg_color;
    colors[ImGuiCol_PopupBg] = bg_color;

    colors[ImGuiCol_Border] = border_color;
    colors[ImGuiCol_BorderShadow] = border_color;

    colors[ImGuiCol_Header] = panel_color;
    colors[ImGuiCol_HeaderHovered] = panel_hover_color;
    colors[ImGuiCol_HeaderActive] = panel_active_color;

    colors[ImGuiCol_Button] = panel_active_color;
    colors[ImGuiCol_ButtonHovered] = light_bg_color;
    colors[ImGuiCol_ButtonActive] = very_light_bg_color;

    colors[ImGuiCol_FrameBg] = panel_color;
    colors[ImGuiCol_FrameBgHovered] = panel_hover_color;
    colors[ImGuiCol_FrameBgActive] = panel_active_color;

    colors[ImGuiCol_Tab] = bg_color;
    colors[ImGuiCol_TabHovered] = panel_hover_color;
    colors[ImGuiCol_TabActive] = panel_active_color;
    colors[ImGuiCol_TabUnfocused] = bg_color;
    colors[ImGuiCol_TabUnfocusedActive] = panel_active_color;

    colors[ImGuiCol_TitleBg] = bg_color;
    colors[ImGuiCol_TitleBgActive] = panel_hover_color;
    colors[ImGuiCol_TitleBgCollapsed] = bg_color;

    colors[ImGuiCol_Text] = text_color;
    colors[ImGuiCol_TextDisabled] = text_disabled_color;
    colors[ImGuiCol_TextSelectedBg] = panel_active_color;

    colors[ImGuiCol_MenuBarBg] = panel_color;

    colors[ImGuiCol_ScrollbarBg] = panel_color;
    colors[ImGuiCol_ScrollbarGrab] = very_light_bg_color;
    colors[ImGuiCol_ScrollbarGrabHovered] = panel_hover_color;
    colors[ImGuiCol_ScrollbarGrabActive] = panel_active_color;

    colors[ImGuiCol_CheckMark] = check_color;

    colors[ImGuiCol_SliderGrab] = panel_hover_color;
    colors[ImGuiCol_SliderGrabActive] = panel_active_color;

    colors[ImGuiCol_Separator] = border_color;
    colors[ImGuiCol_SeparatorHovered] = border_color;
    colors[ImGuiCol_SeparatorActive] = border_color;

    colors[ImGuiCol_ResizeGrip] = bg_color;
    colors[ImGuiCol_ResizeGripHovered] = panel_color;
    colors[ImGuiCol_ResizeGripActive] = light_bg_color;

    colors[ImGuiCol_PlotLines] = panel_active_color;
    colors[ImGuiCol_PlotLinesHovered] = panel_hover_color;
    colors[ImGuiCol_PlotHistogram] = panel_active_color;
    colors[ImGuiCol_PlotHistogramHovered] = panel_hover_color;

    colors[ImGuiCol_DragDropTarget] = bg_color;
    colors[ImGuiCol_NavHighlight] = bg_color;
    colors[ImGuiCol_DockingPreview] = panel_active_color;

    style.WindowPadding = ImVec2(2, 2);
}

void set_light_theme_colors()
{
    constexpr auto color_from_bytes = [](uint8_t r, uint8_t g, uint8_t b)
    {
        return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
    };

    ImGui::StyleColorsLight();

    auto& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    const ImVec4 bg_color = color_from_bytes(230, 230, 230);
    const ImVec4 light_bg_color = color_from_bytes(82, 82, 85);
    const ImVec4 very_light_bg_color = color_from_bytes(90, 90, 95);

    const ImVec4 panel_color = color_from_bytes(166, 199, 214);
    const ImVec4 panel_hover_color = color_from_bytes(191, 224, 240);
    const ImVec4 panel_active_color = color_from_bytes(140, 173, 189);

    const ImVec4 text_color = color_from_bytes(79, 64, 61);
    const ImVec4 text_disabled_color = color_from_bytes(150, 150, 150);
    const ImVec4 border_color = color_from_bytes(190, 190, 190);

    const ImVec4 title_bg_color = color_from_bytes(107, 191, 255);
    const ImVec4 title_collapsed_color = color_from_bytes(102, 166, 204);

    const ImVec4 button_color = color_from_bytes(253, 218, 44);
    const ImVec4 button_hovered = color_from_bytes(107, 209, 255);
    const ImVec4 button_active = color_from_bytes(184, 255, 255);

    const ImVec4 menu_bg_color = color_from_bytes(189, 189, 240);

    const ImVec4 check_color = color_from_bytes(111, 65, 65);;


    colors[ImGuiCol_WindowBg] = ImVec4{ 0.95f, 0.94f, 0.92f, 1.0f };
    colors[ImGuiCol_ChildBg] = bg_color;
    colors[ImGuiCol_PopupBg] = bg_color;

    colors[ImGuiCol_Border] = border_color;
    colors[ImGuiCol_BorderShadow] = border_color;

    colors[ImGuiCol_Header] = panel_color;
    colors[ImGuiCol_HeaderHovered] = panel_hover_color;
    colors[ImGuiCol_HeaderActive] = panel_active_color;

    colors[ImGuiCol_Button] = button_color;
    colors[ImGuiCol_ButtonHovered] = button_hovered;
    colors[ImGuiCol_ButtonActive] = button_active;

    colors[ImGuiCol_FrameBg] = panel_color;
    colors[ImGuiCol_FrameBgHovered] = panel_hover_color;
    colors[ImGuiCol_FrameBgActive] = panel_active_color;

    colors[ImGuiCol_Tab] = bg_color;
    colors[ImGuiCol_TabHovered] = panel_hover_color;
    colors[ImGuiCol_TabActive] = panel_active_color;
    colors[ImGuiCol_TabUnfocused] = bg_color;
    colors[ImGuiCol_TabUnfocusedActive] = panel_active_color;

    colors[ImGuiCol_TitleBg] = panel_hover_color;
    colors[ImGuiCol_TitleBgActive] = title_bg_color;
    colors[ImGuiCol_TitleBgCollapsed] = title_collapsed_color;

    colors[ImGuiCol_Text] = text_color;
    colors[ImGuiCol_TextDisabled] = text_disabled_color;
    colors[ImGuiCol_TextSelectedBg] = panel_active_color;

    colors[ImGuiCol_MenuBarBg] = menu_bg_color;

    colors[ImGuiCol_ScrollbarBg] = panel_color;
    colors[ImGuiCol_ScrollbarGrab] = light_bg_color;
    colors[ImGuiCol_ScrollbarGrabHovered] = light_bg_color;
    colors[ImGuiCol_ScrollbarGrabActive] = very_light_bg_color;

    colors[ImGuiCol_CheckMark] = check_color;

    colors[ImGuiCol_SliderGrab] = panel_hover_color;
    colors[ImGuiCol_SliderGrabActive] = panel_active_color;

    colors[ImGuiCol_Separator] = border_color;
    colors[ImGuiCol_SeparatorHovered] = border_color;
    colors[ImGuiCol_SeparatorActive] = border_color;

    colors[ImGuiCol_DockingPreview] = ImVec4(0.0f, 0.47f, 0.78f, 1.0f);

    style.WindowPadding = ImVec2(2, 2);
}
 
std::unordered_map <std::string, std::any> app_styles{ {"dark", set_dark_theme_colors}, {"light", set_light_theme_colors} };

export struct ui_context
{
    ui_context(GLFWwindow* window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // Load default font
        ImFontConfig fontConfig;
        fontConfig.FontDataOwnedByAtlas = false;
        io.Fonts->AddFontFromMemoryCompressedTTF(g_RobotoBold, g_RobotoBold_size, 18.0f, &fontConfig);
        io.Fonts->AddFontFromMemoryCompressedTTF(g_RobotoItalic, g_RobotoItalic_size, 18.0f, &fontConfig);
        io.FontDefault = io.Fonts->AddFontFromMemoryCompressedTTF(g_RobotoRegular, g_RobotoRegular_size, 18.0f, &fontConfig);

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        std::fstream json_config_file;
        json_config_file.open("ConfigFile.json", std::ios::in);
        nlohmann::json json_data = nlohmann::json::parse(json_config_file);
        json_config_file.close();

        std::any_cast <void (*) ()> (app_styles[json_data["GuiStyle"].get<std::string>()]) ();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 400 core");
    }

    ~ui_context()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void pre_render(bool menu_bar)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create the docking environment
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
            ImGuiWindowFlags_NoBackground;

        if (menu_bar)
            window_flags |= ImGuiWindowFlags_MenuBar;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("InvisibleWindow", nullptr, window_flags);
        ImGui::PopStyleVar(3);

        ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindowDockSpace");

        ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::End();
    }

    void post_render()
    {
        //Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
};