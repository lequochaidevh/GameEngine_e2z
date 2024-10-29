#include "WindowPlatform.h"
#include "pch.h"
#include "Core/Input/InputState.h"

namespace VIEngine {
	NativeWindow* WindowPlatform::Create(EWindowPlatformSpec spec) {
		NativeWindow* window = nullptr;

		switch (spec)
		{
		case VIEngine::EWindowPlatformSpec::GLFW: window = new GLFWPlatformWindow(); break;
		case VIEngine::EWindowPlatformSpec::SDL: VI_ASSERT("SDL Window not supported"); break;
		case VIEngine::EWindowPlatformSpec::None: VI_ASSERT("Unknown Window detected"); break;
		default: VI_ASSERT("Unknown Window detected");
		}
		return window;
	};

	KeyboardInput* WindowPlatform::createKeyboard(EWindowPlatformSpec spec, void* window) {

		KeyboardInput* input = nullptr;
		switch (spec)
		{
		case VIEngine::EWindowPlatformSpec::GLFW: input = new GLFWKeyboardInput(window); break;
		case VIEngine::EWindowPlatformSpec::SDL: VI_ASSERT("SDL Keyboard Input supported"); break;
		case VIEngine::EWindowPlatformSpec::None: VI_ASSERT("Unknown Keyboard Input detected"); break;
		default: VI_ASSERT("Unknown Keyboard detected");
		}
		return input;
	}

	MouseInput* WindowPlatform::createMouse(EWindowPlatformSpec spec, void* window)
	{
		MouseInput* input = nullptr;
		switch (spec)
		{
		case VIEngine::EWindowPlatformSpec::GLFW: input = new GLFWMouseInput(window); break;
		case VIEngine::EWindowPlatformSpec::SDL: VI_ASSERT("SDL Mouse Input supported"); break;
		case VIEngine::EWindowPlatformSpec::None: VI_ASSERT("Unknown Mouse Input detected"); break;
		default: VI_ASSERT("Unknown Mouse detected");
		}
		return input;
	}
}