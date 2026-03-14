#include <vector>
#include <string>

#include "imgui.h"

extern "C" namespace minipro {
    #include "database.h"
    #include "minipro.h"
    #include "xml.h"
}

#include "modals.hpp"
#include "windows.hpp"

using String = std::string;

std::vector<String> device_list;

static inline void renderDeviceInfo(const char* name) {

    ImGui::SameLine();
        const ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;

        if (ImGui::BeginTable("deviceInfo", 2, flags))
        {
            ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Name:");
                ImGui::TableNextColumn();
                ImGui::Text(name);

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

static inline void getDeviceList() {
    
}

void render_window_devices() {
    if (true) // device_list.size() > 0)
        getDeviceList();

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(750, 500), ImVec2(1200, 1200));

    if (ImGui::Begin("Devices List", &(window_states.devicesOpen), ImGuiWindowFlags_NoCollapse)) {
        const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
        const char* data[] = {"This is text for A", "text for B", "yeeppe for C", "o-O", "xxXxXXxXXXxXx"};

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

        static int item_selected_idx = -1; // Here we store our selected data as an index.
        //static bool item_highlight = false;
        //int item_highlighted_idx = -1; // Here we store our highlighted data as an index.
        //ImGui::Checkbox("Highlight hovered item in second listbox", &item_highlight);
        const ImVec2 size = ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, ImGui::GetContentRegionAvail().y);


        if (ImGui::BeginListBox("##empty", size))
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                if (filter.PassFilter(items[n])) {
                
                    const bool is_selected = (item_selected_idx == n);
                    if (ImGui::Selectable(items[n], is_selected))
                        item_selected_idx = n;

                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndListBox();
        }

        ImGui::SameLine();

        if (item_selected_idx >= 0) {
            renderDeviceInfo(data[item_selected_idx]);
        } else {
			const char* text = "No device selected.";
			float spaceWidth = ImGui::GetContentRegionAvail().x;
			float spaceHeight = ImGui::GetContentRegionAvail().y;
			float textWidth = ImGui::CalcTextSize(text).x;
			ImGui::SetCursorPosX((spaceWidth - textWidth) * 0.5f + spaceWidth);
			ImGui::SetCursorPosY(spaceHeight * 0.5f);
			ImGui::Text(text);
        }

        ImGui::End();
    }
}