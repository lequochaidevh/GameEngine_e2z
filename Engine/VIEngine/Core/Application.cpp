#define GLAD_GL_IMPLEMENTATION
#include"Application.h"

#include<GLFW/glfw3.h>
#include "Window/WindowPlatform.h"
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
		/*8.3.5_Add define mEventDispatcher.addEventListener*/
		mEventDispatcher.addEventListener<WindowResizedEvent>(BIND_EVENT_FUNCTION(onWindowResizedEvent));

		return true;
	}
	void Application::Run() {
		CORE_LOG_INFO("App is running: ({0}, {1}, {2})", mConfig.Width, mConfig.Height, mConfig.Title);
		OnInitClient();

		while (!mNativeWindow->ShouldClose()) {
			mNativeWindow->Swapbuffers();

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
		
}
