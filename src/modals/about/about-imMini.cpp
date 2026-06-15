#include "imgui.h"
#include "modals.hpp"

namespace minipro {
	extern "C"  {
		#include "version.h"
	}
}



void render_about_ImMini() {
	ImGui::OpenPopup("About imMinipro");
	if (ImGui::BeginPopupModal("About imMinipro", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("minipro front-end application powered with ImGui");
		ImGui::Separator();

		if (ImGui::BeginTable("aboutTable", 2))
		{
			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Contributors:");
				ImGui::TableNextColumn();
				ImGui::TextLinkOpenURL("Github", "https://github.com/jkvince/imMinipro/graphs/contributors");

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Version:");
				ImGui::TableNextColumn();
				ImGui::Text(IMMINI_VERSION);

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Branch:");
				ImGui::TableNextColumn();
				ImGui::TextLinkOpenURL("master", "https://github.com/jkvince/imMinipro");

			/* TODO: get hash and date from cmake
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
			*/

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("License:");
				ImGui::TableNextColumn();
				ImGui::Text("GNU GPLv3");


			ImGui::EndTable();

		}

	}

}
