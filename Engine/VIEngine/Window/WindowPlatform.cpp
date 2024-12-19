#include "WindowPlatform.h"
#include "pch.h"

namespace VIEngine {
	NativeWindow* WindowPlatform::Create(EWindowPlatformSpec spec) {
		NativeWindow* window = nullptr;

		switch (spec)
		{
		case VIEngine::EWindowPlatformSpec::GLFW: window = new GLFWPlatformWindow();
		case VIEngine::EWindowPlatformSpec::SDL: VI_ASSERT("SDL Window not supported");
		case VIEngine::EWindowPlatformSpec::None: VI_ASSERT("Unknown Window detected");
		default: VI_ASSERT("Unknown Window detected");
		}
		return dynamic_cast<NativeWindow*>(window);
	}
}