#include <string>
#include <vector>

#include "imgui.h"

#include "windows.hpp"
#include "modals.hpp"
#include "manage-programmer.hpp"
#include "device-list.hpp"


window_states_t window_states = {
    false, // devicesOpen
    false  // fileOpen
};


void RenderWindows() {
    if (window_states.devicesOpen == true) {
        render_window_devices();
    }

    if (window_states.fileOpen == true) {
        if (ImGui::Begin("File", &(window_states.fileOpen), ImGuiWindowFlags_NoCollapse)) {

            // TODO: add native file dialog
            ImGui::Text("Some text");
            ImGui::Separator();
            ImGui::Text("more text");
            ImGui::End();
        }
    }

    RenderManageProgrammerWindows();
}