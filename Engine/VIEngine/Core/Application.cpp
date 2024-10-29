#define GLAD_GL_IMPLEMENTATION
#include"Application.h"

#include<GLFW/glfw3.h>
#include "Window/WindowPlatform.h"

//#include "Input/InputState.h"
namespace VIEngine {
	
    Application::Application(const ApplicationConfiguration& config) : mConfig(config){//}, mEventDispatcher() {
		//Logger::Init();
		mNativeWindow.reset(WindowPlatform::Create(config.WindowSpec)); //reset unique_ptr
	}
	bool Application::Init() {
		
		if (!mNativeWindow->Init(mConfig, &mEventDispatcher)) {
			CORE_LOG_CRITICAL("Window_spec created failed");
			return false;
		}
		/*9.1.3.2_Set value mInputState */
		mInputState = mNativeWindow->GetInputState();
		/*8.3.5_Add define mEventDispatcher.addEventListener*/
		mEventDispatcher.addEventListener<WindowResizedEvent>(BIND_EVENT_FUNCTION(onWindowResizedEvent));

		/*9.1.3.2_Add define mEventDispatcher.addEventListener*/
		mEventDispatcher.addEventListener<KeyPressedEvent>(BIND_EVENT_FUNCTION(onKeyPressedEvent));
		mEventDispatcher.addEventListener<KeyHeldEvent>(BIND_EVENT_FUNCTION(onKeyHeldEvent));
		mEventDispatcher.addEventListener<KeyReleasedEvent>(BIND_EVENT_FUNCTION(onKeyReleasedEvent));
		mEventDispatcher.addEventListener<MouseMovedEvent>(BIND_EVENT_FUNCTION(onMouseMovedEvent));
		mEventDispatcher.addEventListener<MouseScrolledEvent>(BIND_EVENT_FUNCTION(onMouseScrolledEvent));
		mEventDispatcher.addEventListener<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(onMouseButtonPressedEvent));
		mEventDispatcher.addEventListener<MouseButtonHeldEvent>(BIND_EVENT_FUNCTION(onMouseButtonHeldEvent));
		mEventDispatcher.addEventListener<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(onMouseButtonReleasedEvent));
		return true;
	}
	void Application::Run() {
		CORE_LOG_INFO("App is running: ({0}, {1}, {2})", mConfig.Width, mConfig.Height, mConfig.Title);
		OnInitClient();

		while (!mNativeWindow->ShouldClose()) {
			mNativeWindow->Swapbuffers();
			//if (mInputState->Mouse->IsPressed(EMouseButton::BUTTON_LEFT)) {
			//	CORE_LOG_TRACE("Left mouse is clicked");
			//}
			//
			//if (mInputState->Mouse->IsPressed(EMouseButton::BUTTON_RIGHT)) {
			//	CORE_LOG_TRACE("Right mouse is clicked");
			//}
			//if (mInputState->Keyboard->IsPressed(EKeyCode::A)) {
			//	CORE_LOG_TRACE("A key is pressed");
			//}
			//if (mInputState->Keyboard->IsReleased(EKeyCode::A)) {
			//	CORE_LOG_TRACE("A key is released");
			//}
			mNativeWindow->PollsEvent();

		}

		OnShutdownClient();
	}
	void Application::Shutdown() {
		mNativeWindow->Shutdown();
	}

	bool Application::onWindowResizedEvent(const WindowResizedEvent& windowResizedEvent){
		CORE_LOG_TRACE("(Width : {0}, Height : {1})", windowResizedEvent.getWidth(), windowResizedEvent.getHeight());
		return false;

	}
	/*9.1.3.3_Define function onEvent*/
	bool Application::onKeyPressedEvent(const KeyPressedEvent& eventContext) {
		CORE_LOG_TRACE("Key {0} is pressed", (char)eventContext.getKeyCode());
		return false;
	}

	bool Application::onKeyHeldEvent(const KeyHeldEvent& eventContext) {
		CORE_LOG_TRACE("Key {0} is held", (char)eventContext.getKeyCode());
		return false;
	}

	bool Application::onKeyReleasedEvent(const KeyReleasedEvent& eventContext) {
		CORE_LOG_TRACE("Key {0} is released", (char)eventContext.getKeyCode());
		return false;
	}

	bool Application::onMouseMovedEvent(const MouseMovedEvent& eventContext) {
		CORE_LOG_TRACE("Mouse position: {0}, {1}. Mouse relative: {2}, {3}", eventContext.getPositionX(), eventContext.getPositionY(), eventContext.getOffsetX(), eventContext.getOffsetY());
		return false;
	}

	bool Application::onMouseScrolledEvent(const MouseScrolledEvent& eventContext) {
		CORE_LOG_TRACE("Mouse scroll X: {0}, Mouse Scroll Y: {1}", eventContext.getScrollX(), eventContext.getScrollY());
		return false;
	}

	bool Application::onMouseButtonPressedEvent(const MouseButtonPressedEvent& eventContext) {
		CORE_LOG_TRACE("Mouse button {0} is pressed", eventContext.getButton());
		return false;
	}

	bool Application::onMouseButtonHeldEvent(const MouseButtonHeldEvent& eventContext) {
		CORE_LOG_TRACE("Mouse button {0} is held", eventContext.getButton());
		return false;
	}

	bool Application::onMouseButtonReleasedEvent(const MouseButtonReleasedEvent& eventContext) {
		CORE_LOG_TRACE("Mouse button {0} is released", eventContext.getButton());
		return false;
	}
}
