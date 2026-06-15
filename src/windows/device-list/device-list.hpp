#pragma once
#include <cstddef>
#include <vector>
#include <string>

#include "uiwindow.hpp"

using String = std::string;

namespace minipro {
	extern "C" {
		#include "database.h"
		#include "xml.h"
	}
}

class DeviceListWindow : public UIWindow {
	public:
		DeviceListWindow();
		void Render() override;
		int DeviceListCallback(int type, const char *tag, size_t taglen, minipro::Parser *parser);
		static int CallbackWrapper(int type, const char *tag, size_t taglen, minipro::Parser *parser);

	private:
		static DeviceListWindow* currentInstance;
		std::vector<String> device_list;

		void GetDeviceList();
		static int tagcmpn(const char *tag, size_t taglen, const char *str);
		static void RenderDeviceInfo(const char* name);

};
