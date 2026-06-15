#pragma once

class UIWindow {
	public:
		UIWindow();
		bool is_open;

		virtual void Render() = 0;


};
