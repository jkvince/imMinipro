#include "imgui.h"
#include "modals.hpp"

void render_createChip() {
    ImGui::OpenPopup("Create New Chip");
    if (ImGui::BeginPopupModal("Create New Chip", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Create chip");
    }

}