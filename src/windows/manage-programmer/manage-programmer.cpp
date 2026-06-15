#include <iostream>
#include <string>
#include <cstddef>

#include "imgui.h"

#include "modals.hpp"
#include "usb-handler.hpp"
#include "uiwindow.hpp"
#include "manage-programmer.hpp"

namespace minipro {
	extern "C"  {
		#include "minipro.h"
	}
}

using String = std::string;


ManageProgrammerWindow::ManageProgrammerWindow(minipro::minipro_handle_t* handle_in) {
	handle = handle_in;
}

void ManageProgrammerWindow::Render() {
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSizeConstraints(ImVec2(250, 200), ImVec2(1200, 1200));

	String win_name = "Manage ";
	win_name += handle->model;
	win_name += "-";
	win_name.append(handle->serial_number, 5);
	if (ImGui::Begin(win_name.c_str(), &is_open, ImGuiWindowFlags_NoCollapse)) {
		if (ImGui::BeginTable("mainTable", 2)) {

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Model");
				ImGui::TableNextColumn();
				ImGui::Text("%s", handle->model);

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Device code");
				ImGui::TableNextColumn();
				ImGui::Text("%s", handle->device_code);

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Serial number");
				ImGui::TableNextColumn();
				ImGui::Text("%s", handle->serial_number);

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Manufacture date");
				ImGui::TableNextColumn();
				ImGui::Text("%s", handle->mfg_date);

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
