#include "Application.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

namespace Ether
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

    void Application::InitImGui(GLFWwindow *window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext(NULL);
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void Application::CreateNewFrameImGui()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void Application::RenderImGui()
    {
        //Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Application::CleanUpImGui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

	void Application::Run()
	{
        GLFWwindow* window;

        if (!glfwInit())
            exit(EXIT_FAILURE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        window = glfwCreateWindow(1280, 720, "ImGuiExample", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        glfwSwapInterval(1);
        InitImGui(window);

        bool no_titlebar = false;
        bool no_scrollbar = false;
        bool no_menu = false;
        bool no_move = false;
        bool no_resize = false;
        bool no_collapse = false;
        bool no_close = false;
        bool no_nav = false;
        bool no_background = false;
        bool no_bring_to_front = false;
        bool no_docking = false;
        
        bool open = false;
        bool* p_open = &open;

        ImGuiWindowFlags window_flags = 0;
        if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
        if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
        if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
        if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
        if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
        if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
        if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
        if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
        if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;
        if (no_close)           p_open = NULL; // Don't pass our bool* to Begin


        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

            CreateNewFrameImGui();

            ImGui::Begin("MyWindow1 ", p_open, window_flags);

            ImGui::Text("Hello,I'm using ImGui Version:(%s) to Create real time GUI", IMGUI_VERSION);

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("Menu"))
                {
                    ImGui::MenuItem("(dummy menu)", NULL, false, false);
                    if (ImGui::MenuItem("Open", "Ctrl + O")) {}
                    if (ImGui::BeginMenu("More"))
                    {
                        ImGui::MenuItem("More1");
                        ImGui::MenuItem("More2");
                        ImGui::MenuItem("More3");
                        ImGui::MenuItem("More4");
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

            ImGui::End();

            ImGui::ShowDemoWindow();

            RenderImGui();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        CleanUpImGui();

        glfwDestroyWindow(window);

        glfwTerminate();
        exit(EXIT_SUCCESS);
	}
}