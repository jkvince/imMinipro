#include <iostream>
#include <string>

#include "imgui.h"

#include "modals.hpp"
#include "usb-handler.hpp"

extern "C" namespace minipro {
    #include "minipro.h"
}

using String = std::string;

bool windowactive = false;

void openProgrammerWindow() {
    windowactive = true;
}


void CreateManageProgrammerWindow(minipro::minipro_handle_t* handle) {
    
    if (!handle) return;
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(250, 200), ImVec2(1200, 1200));
    String win_name = "Manage ";
    win_name += handle->model;
    win_name += "-";
    win_name.append(handle->serial_number, 5);
    if (ImGui::Begin(win_name.c_str(), &windowactive, ImGuiWindowFlags_NoCollapse)) {
        if (ImGui::BeginTable("mainTable", 2)) {
            
            ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Model");
                ImGui::TableNextColumn();
                ImGui::Text(handle->model);                

            ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Device code");
                ImGui::TableNextColumn();
                ImGui::Text(handle->device_code);
            
            ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Serial number");
                ImGui::TableNextColumn();
                ImGui::Text(handle->serial_number);

            ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Manufacture date");
                ImGui::TableNextColumn();
                ImGui::Text(handle->mfg_date);



            ImGui::EndTable();

        }

        if (ImGui::Button("Update Firmware", ImVec2(120, 0)))
            SetModalState(UPDATE_FIRMWARE);
        ImGui::SameLine();
        ImGui::Text("Current Firmware: %s", handle->firmware_str);
        // TODO: add check if out of date

        ImGui::End();
    }
}

void RenderManageProgrammerWindows() {
    if (windowactive) {
        for (const auto& handle : programmer_handles) {
            CreateManageProgrammerWindow(handle);
        }
    }
}