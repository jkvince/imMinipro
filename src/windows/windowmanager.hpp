#pragma once
#include <memory>
#include <vector>


#include "uiwindow.hpp"

class WindowManager {
	public:
		WindowManager();
		~WindowManager();

		static WindowManager* Instance;

		void Render();
		void AddWindow(std::unique_ptr<UIWindow> window);

	private:
		std::vector<std::unique_ptr<UIWindow>> windows;

};
