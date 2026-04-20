#include "imgui.h"

#include "windows.hpp"

void render_settings() {

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(750, 500), ImVec2(1200, 1200));

    if (ImGui::Begin("Settings", &(window_states.settingsOpen), ImGuiWindowFlags_NoCollapse)) {

        ImGui::Text("Some text");
        ImGui::Separator();
        ImGui::Text("more text");
        ImGui::End();
    }

}