#pragma once

#include "Window.h"

namespace VIEngine {
	//Factory class
/*6.2.3_Create WindowPlatform*/

	class  WindowPlatform
	{
	public:
		static NativeWindow* Create(EWindowPlatformSpec spec);
	private:
		WindowPlatform() = default;
		WindowPlatform(WindowPlatform&) = default;
		~WindowPlatform() = default;
	};	 
}