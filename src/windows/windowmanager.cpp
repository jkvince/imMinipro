#include <cstdio>
#include <memory>
#include <vector>

#include "imgui.h"

#include "modals.hpp"
#include "manage-programmer.hpp"
#include "device-list.hpp"
#include "uiwindow.hpp"
#include "windowmanager.hpp"

WindowManager* WindowManager::Instance = nullptr;

WindowManager::WindowManager() {
	Instance = this;
}

WindowManager::~WindowManager() {
	Instance = nullptr;
}

void WindowManager::Render() {
		for (auto window = windows.begin(); window != windows.end();) {
			if ((*window)->is_open) {
				(*window)->Render();
				window++;
			} else {
				window = windows.erase(window);
			}
		}
}

void WindowManager::AddWindow(std::unique_ptr<UIWindow> window) {
			windows.push_back(std::move(window));
}
