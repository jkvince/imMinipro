#include <stdio.h>
#include <cstdlib>

#include "imgui.h"

#include "modals.hpp"

#include "about-imgui.hpp"
#include "about-imMini.hpp"
#include "about-minipro.hpp"
#include "about-nativefiledialog.hpp"

#include "generate-chip.hpp"
#include "update-firmware.hpp"
#include "programmer-read.hpp"
#include "programmer-write.hpp"

ModalEnum ModalState = NO_MODAL;

void SetModalState(ModalEnum newState) {
	ModalState = newState;
}

void RenderModals() {
	if (ModalState == NO_MODAL) {
		return;
	}

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	switch (ModalState) {
	case PROGRAMMER_WRITE:
		render_programmer_write();
		break;

	case PROGRAMMER_READ:
		render_programmer_read();
		break;

	case UPDATE_FIRMWARE:
		render_update_firmware();
		break;

	case CREATE_CHIP:
		render_createChip();
		break;

	case ABOUT_IM_MINI:
		render_about_ImMini();
		break;

	case ABOUT_MINIPRO:
		render_about_Minipro();
		break;

	case ABOUT_IMGUI:
		render_about_ImGui();
		break;

	case ABOUT_NATIVEFILEDIALOG:
		render_about_nativefiledialog();
		break;


	default:
		printf("Modal state invalid!\n");
		exit(EXIT_FAILURE);

	}

	const char* close_text = "Close";
	ImVec2 textSize = ImGui::CalcTextSize(close_text);
	float buttonWidth = textSize.x + 16.0f;
	float windowCenterX = ImGui::GetWindowWidth() * 0.5f;
	float centerX = windowCenterX - (buttonWidth * 0.5f);
	ImGui::SetCursorPosX(centerX);

	if (ImGui::Button(close_text)) {
		ImGui::CloseCurrentPopup();
		SetModalState(NO_MODAL);
	}
	ImGui::EndPopup();
}
