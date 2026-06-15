#include "imgui.h"
#include "modals.hpp"

namespace minipro {
	extern "C"  {
		#include "version.h"
	}
}


void render_programmer_write() {
	ImGui::OpenPopup("Write");
	if (ImGui::BeginPopupModal("Write", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("Write thing goes here");

	}

}
