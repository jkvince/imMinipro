#include "imgui.h"
#include "modals.hpp"


void render_about_nativefiledialog() {
	ImGui::OpenPopup("About NativeFileDialog");
	if (ImGui::BeginPopupModal("About NativeFileDialog", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("Cross platform (Windows, Mac, Linux) native file dialog library\n with C and C++ bindings, based on mlabbe/nativefiledialog.");
		ImGui::Separator();

		if (ImGui::BeginTable("aboutTable", 2))
		{
			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Contributors:");
				ImGui::TableNextColumn();
				ImGui::TextLinkOpenURL("Github", "https://github.com/btzy/nativefiledialog-extended/graphs/contributors");

			/* TODO: fetch version from git
			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Version:");
				ImGui::TableNextColumn();
				ImGui::Text("");
			*/

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Branch:");
				ImGui::TableNextColumn();
				ImGui::TextLinkOpenURL("master", "https://github.com/btzy/nativefiledialog-extended/tree/master");

			/*
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

			*/

			ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("License:");
				ImGui::TableNextColumn();
				ImGui::Text("Zlib");

			ImGui::EndTable();

		}

	}

}
