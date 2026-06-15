#pragma once

#include "uiwindow.hpp"

namespace minipro {
	extern "C"  {
		#include "minipro.h"
	}
}

class ManageProgrammerWindow : public UIWindow {
	public:
		ManageProgrammerWindow(minipro::minipro_handle_t* handle_in);

		void Render() override;

	private:
		minipro::minipro_handle_t* handle;
};
