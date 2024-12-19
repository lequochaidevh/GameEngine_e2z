#pragma once

#include "Window.h"

namespace VIEngine {
	//Factory class
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