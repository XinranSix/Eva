/**
 * @file    :   ImGuiLayer.cpp
 * @date    :   2023/06/28 19:16:19
 * @author  :   yaojie
 * @version :   1.0
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ImGuiLayer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Application.h"
#include "eva/Core.h"

namespace Eva {

    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::OnAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO &io = ImGui::GetIO();
        // io.BackendFlags != ImGuiBackendFlags_HasMouseCursors;
        // io.BackendFlags != ImGuiBackendFlags_HasSetMousePos;

        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void ImGuiLayer::OnDetach() {}

    void ImGuiLayer::OnUpdate() {

        ImGuiIO &io = ImGui::GetIO();
        Application &app = Application::Get();
        io.DisplaySize =
            ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(
            EVA_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(
            EVA_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(
            EVA_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(
            EVA_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(
            EVA_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(
            EVA_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<KeyTypedEvent>(
            EVA_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(
            EVA_BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());

        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffset();
        io.MouseWheel += e.GetYOffset();

        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] ||
                     io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] ||
                      io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt =
            io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] ||
                      io.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        int keycode = e.GetKeyCode();
        io.AddInputCharacter((unsigned int)keycode);
        // if (keycode > 0 && keycode < 0x10000) {
        //     io.AddInputCharacter((unsigned int)keycode);
        // }
        return false;
    }

    // 处理窗口大小变化
    bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, e.GetWidth(), e.GetHeight());

        return false;
    }

} // namespace Eva
