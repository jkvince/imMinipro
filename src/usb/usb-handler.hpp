#pragma once

#include <vector>

extern "C" namespace minipro {
    #include "minipro.h"
}


extern std::vector<minipro::minipro_handle_t*> programmer_handles;

void usb_handler_cleanup();
void UpdateUsbDevices();