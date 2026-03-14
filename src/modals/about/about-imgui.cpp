#include "imgui.h"
#include "modals.hpp"


void render_about_ImGui() {
    ImGui::OpenPopup("About ImGui");
    if (ImGui::BeginPopupModal("About ImGui", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Bloat-free Graphical User interface for C++ with minimal dependencies");
        ImGui::Separator();
        
        if (ImGui::BeginTable("aboutTable", 2))
        {
            ImGui::TableNextRow();    
                ImGui::TableNextColumn();
                ImGui::Text("Contributors:");
                ImGui::TableNextColumn();
                ImGui::TextLinkOpenURL("Github", "https://github.com/ocornut/imgui/graphs/contributors");

            ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Version:");
                ImGui::TableNextColumn();
                ImGui::Text("1.92.7");

            ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Branch:");
                ImGui::TableNextColumn();
                ImGui::TextLinkOpenURL("master", "https://github.com/ocornut/imgui/tree/master");

            ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Git hash:");
                ImGui::TableNextColumn();
                ImGui::Text("41765fbda723d23e04e98afec40447d149d02ec8");

            ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Git date:");
                ImGui::TableNextColumn();
                ImGui::Text("Mar 6, 2026");

            ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("License:");
                ImGui::TableNextColumn();
                ImGui::Text("MIT");

            ImGui::EndTable();

        }

    }

}