#include <bits/types/mbstate_t.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>

#include "imgui.h"

namespace minipro {
	extern "C" {
		#include "database.h"
		#include "xml.h"
	}
}

#include "modals.hpp"
#include "windowmanager.hpp"
#include "uiwindow.hpp"
#include "device-list.hpp"

using String = std::string;

DeviceListWindow* DeviceListWindow::currentInstance = nullptr;

DeviceListWindow::DeviceListWindow() : UIWindow() {
	GetDeviceList();
}

void DeviceListWindow::Render() {
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSizeConstraints(ImVec2(750, 500), ImVec2(1200, 1200));

	if (ImGui::Begin("Devices List", &is_open, ImGuiWindowFlags_NoCollapse)) {
		const char* data = "This is text for A";

		static ImGuiTextFilter filter;
		filter.Draw();
		ImGui::SameLine();
		ImGui::Text("<?>");
		ImGui::SetItemTooltip("Filter usage:\n"
		"  \"\"         display all lines\n"
		"  \"xxx\"      display lines containing \"xxx\"\n"
		"  \"xxx,yyy\"  display lines containing \"xxx\" or \"yyy\"\n"
		"  \"-xxx\"     hide lines containing \"xxx\"");
		ImGui::SameLine();
		if (ImGui::Button("New Chip")) SetModalState(CREATE_CHIP);

		static int item_selected_idx = -1;
		const ImVec2 size = ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, ImGui::GetContentRegionAvail().y);

		if (ImGui::BeginListBox("##empty", size)) {
			float item_height = ImGui::GetTextLineHeightWithSpacing();
			ImGuiListClipper clipper;
			clipper.Begin(static_cast<int>(device_list.size()), item_height);

			while (clipper.Step()) {
				for (int i = clipper.DisplayStart; i<clipper.DisplayEnd; i++) {
					if (!filter.PassFilter(device_list[i].c_str()))
						continue;

					const bool is_selected = (item_selected_idx == (int) i);

					if (ImGui::Selectable(device_list[i].c_str(), is_selected))
						item_selected_idx = i;

					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
			}

			clipper.End();
			ImGui::EndListBox();

		}

		ImGui::SameLine();

		if (item_selected_idx >= 0) {
			RenderDeviceInfo(data);
		} else {
			const char* text = "No device selected.";
			float spaceWidth = ImGui::GetContentRegionAvail().x;
			float spaceHeight = ImGui::GetContentRegionAvail().y;
			float textWidth = ImGui::CalcTextSize(text).x;
			ImGui::SetCursorPosX((spaceWidth - textWidth) * 0.5f + spaceWidth);
			ImGui::SetCursorPosY(spaceHeight * 0.5f);
			ImGui::Text("%s", text);
		}

		ImGui::End();
	}
}

typedef struct {
	bool done;
} MyState;

int DeviceListWindow::DeviceListCallback(int type, const char *tag, size_t taglen, minipro::Parser *parser) {
	MyState *state = (MyState *)parser->userdata;

	if (state->done) return minipro::XML_OK;
	/* Text content that appeared BEFORE this tag (may be empty). */
	// if (parser->contentlen > 0) {
	// 	indent(parser->level);
	// 	printf("TEXT: \"%.*s\"\n", (int)parser->contentlen, parser->content);
	// }

	switch (type) {

	case minipro::OPENTAG_:
	case minipro::SELFCLOSE_:

		if (!tagcmpn(tag, taglen, "manufacturer")) {}

		else if (!tagcmpn(tag, taglen, "custom")) {}

		if (!tagcmpn(tag, taglen, "ic")) {
			minipro::Memblock mb_name = minipro::get_attribute(tag, taglen, "name");
			if (!mb_name.b)
				return EXIT_FAILURE;

			device_list.push_back(String(mb_name.b, mb_name.z));

		}

		break;

	case minipro::FRAMECLOSE_:
		if (!tagcmpn(tag, taglen, "configurations"))
			state->done = true;
		break;

	}

	return minipro::XML_OK; /* keep going */
}

int DeviceListWindow::CallbackWrapper(int type, const char *tag, size_t taglen, minipro::Parser *parser) {
	return currentInstance->DeviceListCallback(type, tag, taglen, parser);
}

void DeviceListWindow::GetDeviceList() {
	FILE* f = fopen("infoic.xml", "rb");
	if (!f) exit(EXIT_FAILURE);

	MyState state = { 0 };
	state.done = false;
	minipro::Parser p = { 0 };
	p.inputcbdata = f;
	currentInstance = this;
	p.worker = CallbackWrapper;
	p.userdata = &state;

	int _ = minipro::parse(&p);

	minipro::done(&p);
	fclose(f);
}

int DeviceListWindow::tagcmpn(const char *tag, size_t taglen, const char *str) {
	if (!tag || !str || !taglen)
		return 1;

	/* Find the start of substring */
	for (; taglen; taglen--, tag++) {
		if (isprint((unsigned char)*tag) &&
		    !isspace((unsigned char)*tag))
			break;
	}

	/* Find the end of substring */
	size_t len = 0;
	for (; taglen; taglen--, len++) {
		if (iscntrl((unsigned char)tag[len]) ||
		    isspace((unsigned char)tag[len]))
			break;
	}

	if (!len || len < strlen(str))
		return 1;
	return strncasecmp(tag, str, len);
}

void DeviceListWindow::RenderDeviceInfo(const char* name) {

	ImGui::SameLine();
	const ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;

	if (ImGui::BeginTable("deviceInfo", 2, flags))
	{
		ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text("Name:");
			ImGui::TableNextColumn();
			ImGui::Text("%s", name);

		ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text("Memory:");
			ImGui::TableNextColumn();
			ImGui::Text("1024 bytes");

		ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text("Package:");
			ImGui::TableNextColumn();
			ImGui::Text("DIP8");

		ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text("Protocol:");
			ImGui::TableNextColumn();
			ImGui::Text("0x01");

		ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text("Read buffer size:");
			ImGui::TableNextColumn();
			ImGui::Text("128 bytes");

		ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text("Write buffer size:");
			ImGui::TableNextColumn();
			ImGui::Text("16 bytes");

		ImGui::EndTable();

	}
}
