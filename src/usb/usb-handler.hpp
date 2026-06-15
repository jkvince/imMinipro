#pragma once

#include <vector>

namespace minipro {
	extern "C"  {
    	#include "minipro.h"
	}
}



extern std::vector<minipro::minipro_handle_t*> programmer_handles;

void usb_handler_cleanup();
void UpdateUsbDevices();
