#include "imgui.h"
#include "modals.hpp"

namespace minipro {
	extern "C"  {
		#include "version.h"
	}
}


void render_about_Minipro() {
	ImGui::OpenPopup("About minipro");
	if (ImGui::BeginPopupModal("About minipro", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("An open source program for controlling the MiniPRO TL866xx series of chip programmers");
		ImGui::Separator();

		if (ImGui::BeginTable("aboutTable", 2))
		{
			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Contributors:");
				ImGui::TableNextColumn();
				ImGui::TextLinkOpenURL("Gitlab", "https://gitlab.com/DavidGriffith/minipro/-/graphs/master");

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Version:");
				ImGui::TableNextColumn();
				ImGui::Text(VERSION);

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Branch:");
				ImGui::TableNextColumn();
				ImGui::TextLinkOpenURL(GIT_BRANCH, "https://gitlab.com/DavidGriffith/minipro");

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Git hash:");
				ImGui::TableNextColumn();
				ImGui::Text(GIT_HASH);

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Git date:");
				ImGui::TableNextColumn();
				ImGui::Text(GIT_DATE);

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("License:");
				ImGui::TableNextColumn();
				ImGui::Text("GNU GPLv3");

			ImGui::EndTable();

		}

	}

}
