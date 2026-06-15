#include <vector>

namespace minipro {
	extern "C"  {
		#include "usb.h"
		#include "minipro.h"
	}
}


std::vector<minipro::minipro_handle_t*> programmer_handles;


void usb_handler_cleanup() {
	for (const auto& handle : programmer_handles) minipro::minipro_close(handle);
}

static int get_devices_count() {
	//TODO: make this more efficient
	return minipro::minipro_get_devices_count(MP_TL866A)
		+ minipro::minipro_get_devices_count(MP_TL866IIPLUS)
		+ minipro::minipro_get_devices_count(MP_T76);
}

void UpdateUsbDevices() {
	// check if device change
	size_t current_count = get_devices_count();

	if (current_count != programmer_handles.size()) {
		// close and empty
		for (const auto& handle : programmer_handles) minipro::minipro_close(handle);
		programmer_handles.clear();


		for (size_t x=0; x<current_count; x++) {
			minipro::minipro_handle_t* handle = minipro::minipro_open(minipro::VERBOSE);
			if (handle) {
				programmer_handles.push_back(handle);
			}

		}

	}


}
