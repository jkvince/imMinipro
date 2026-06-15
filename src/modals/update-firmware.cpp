#include "imgui.h"

void render_update_firmware() {
	ImGui::OpenPopup("Read");
	if (ImGui::BeginPopupModal("Read", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("AAAAA");
	}
}
