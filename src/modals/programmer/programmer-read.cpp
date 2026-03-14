#include <string>

#include "imgui.h"

#include "modals.hpp"
#include "usb-handler.hpp"

using String = std::string;

void render_programmer_read() {
    ImGui::OpenPopup("Read");
    if (ImGui::BeginPopupModal("Read", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        static int programmer_selected_id = 0;
        int amount = static_cast<int>(programmer_handles.size());


        if (amount > 0) {
            if (ImGui::BeginCombo("Programmer", programmer_handles[programmer_selected_id]->model, 0)) {
                for (int n=0; n < amount; n++) {
                    const bool is_selected = (programmer_selected_id == n);
                    String item_name = programmer_handles[n]->model;
                    item_name += "-";
                    item_name.append(programmer_handles[n]->serial_number, 5);
                    if (ImGui::Selectable(item_name.c_str()), is_selected) {
                        programmer_selected_id = n;
                    }
                }
                ImGui::EndCombo();
            }
        } else {

            ImGui::BeginDisabled(true);
            if (ImGui::BeginCombo("Programmer", "No Programmer found", ImGuiComboFlags_NoArrowButton)) {
                ImGui::EndCombo();
            }
            ImGui::EndDisabled();
        }
        

        static int item_selected_idx = 0;
        const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
        // Here we store our selection data as an index.
        const char* combo_preview_value = items[item_selected_idx];

        ImGui::SameLine();

        if (ImGui::BeginCombo("Device", combo_preview_value, ImGuiComboFlags_HeightLargest))
        {
            static ImGuiTextFilter filter;
            if (ImGui::IsWindowAppearing())
            {
                ImGui::SetKeyboardFocusHere();
                filter.Clear();
            }
            ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F);
            filter.Draw("##Filter", -FLT_MIN);

            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                const bool is_selected = (item_selected_idx == n);
                if (filter.PassFilter(items[n]))
                    if (ImGui::Selectable(items[n], is_selected))
                        item_selected_idx = n;
            }
            ImGui::EndCombo();
        }

        if (ImGui::TreeNode("Additional options"))
        {
            ImGui::Text("Set voltage");
            ImGui::TreePop();
        }


        ImGui::BeginDisabled(true);
        if (ImGui::Button("Read")) {}
        ImGui::EndDisabled();
        ImGui::SameLine();

        static float progress = 0.0f;
        progress += 0.25f * ImGui::GetIO().DeltaTime;
        if (progress > 1.0f) progress = 0.0f;
        ImGui::ProgressBar(progress, ImVec2(-1.0f, 0.0f));

    }

}