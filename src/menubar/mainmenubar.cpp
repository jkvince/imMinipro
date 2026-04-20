/*
Main menu bar

*/
#include <string>
#include <iostream>

#include "imgui.h"

#include "main.hpp"
#include "modals.hpp"
#include "windows.hpp"
#include "manage-programmer.hpp"
#include "usb-handler.hpp"

extern "C" namespace minipro {
    #include "usb.h"
}

using String = std::string;

static inline void MenuFile()
{
    if (ImGui::MenuItem("Open File...", "Ctrl+O"))
        window_states.fileOpen = true;
    if (ImGui::MenuItem("Save File...", "Ctrl+S")) {}
    if (ImGui::BeginMenu("Open Recent"))
    {
        ImGui::MenuItem("file1.bin");
        ImGui::SetItemTooltip("/dir/folder/file1.bin");
        ImGui::MenuItem("file2.bin");
        ImGui::MenuItem("file3.bin");
        ImGui::EndMenu();
    }
    ImGui::Separator();

    if (ImGui::MenuItem("Find...", "Ctrl+F")) {}
    if (ImGui::MenuItem("Goto...", "Ctrl+G")) {}

    ImGui::Separator();

    if (ImGui::MenuItem("Quit imMinipro", "Alt+F4")) {
        ImMini_quit();
    }
}

/*
const char* versionToString(uint8_t version) {
    switch (version) {
	case MP_TL866A: return "TL866A";
	case MP_TL866CS: return "TL866CS";
	case MP_TL866IIPLUS: return "TL866IIPLUS";
    case MP_T48: return "T48";
	case MP_T56: return "T56";
	case MP_T76: return "T76";
	default: 
        std::cerr << "Unknwon programmer version" << std::endl;
        return nullptr;
	}
}
*/


static inline void RenderProgrammerList() {
    if (programmer_handles.size() > 0) {
        for (const auto& handle : programmer_handles) {
            String item_name = handle->model;
            item_name += "-";
            item_name.append(handle->serial_number, 5);
            if (ImGui::MenuItem(item_name.c_str())) {
                openProgrammerWindow();
            }
        }
    } else {
        ImGui::BeginDisabled(true);
        ImGui::MenuItem("No programmers found");
        ImGui::EndDisabled();
    }
}


static inline void MenuProgrammers() {
    if (ImGui::MenuItem("Read...", "Ctrl+R"))
        SetModalState(PROGRAMMER_READ);
    if (ImGui::MenuItem("Write...", "Ctrl+W"))
        SetModalState(PROGRAMMER_WRITE);
    ImGui::Separator();
    RenderProgrammerList();

}

static inline void MenuDevices() {
    if (ImGui::MenuItem("Devices List..."))
        window_states.devicesOpen = true;
}

static inline void MenuExtras() {
    if (ImGui::MenuItem("Settings..."))
        window_states.settingsOpen = true;
}

static inline void MenuAbout() {
    if (ImGui::MenuItem("imMinipro..."))
        SetModalState(ABOUT_IM_MINI);
    
    if (ImGui::MenuItem("minipro..."))
        SetModalState(ABOUT_MINIPRO);
    
    if (ImGui::MenuItem("Dear ImGui..."))
        SetModalState(ABOUT_IMGUI);

}

void RenderMainMenuBar() {
    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {
            MenuFile();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Programmers")) {
            MenuProgrammers();
            ImGui::EndMenu();
        }
        
        // devices are the chips 
        if (ImGui::BeginMenu("Devices")) {
            MenuDevices();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Extras")) {
            MenuExtras();
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("About")) {
            MenuAbout();
            ImGui::EndMenu();
        }

        #ifdef DEBUG
            if (ImGui::MenuItem("Demo"))
                createDemoWindow();
        #endif

        ImGui::EndMainMenuBar();

    }

}