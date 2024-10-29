#pragma once

#include "Window.h"

namespace VIEngine {
	//Factory class
/*6.2.3_Create WindowPlatform*/

	class  WindowPlatform
	{
	public:
		static NativeWindow* Create(EWindowPlatformSpec spec);

		/*9.1.1.6_Add create ptr Keyboard Mouse */
		static class KeyboardInput* createKeyboard(EWindowPlatformSpec spec, void* window);
		static class MouseInput* createMouse(EWindowPlatformSpec spec, void* window);
	private:
		WindowPlatform() = default;
		//WindowPlatform(WindowPlatform&) = default;
		~WindowPlatform() = default;
	};	 
}