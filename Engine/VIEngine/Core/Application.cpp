#define GLAD_GL_IMPLEMENTATION
#include"Application.h"

#include<GLFW/glfw3.h>
#include "Window/WindowPlatform.h"
namespace VIEngine {
    Application::Application(const ApplicationConfiguration& config) : mConfig(config) {
		//Logger::Init();
		mNativeWindow.reset(WindowPlatform::Create(config.WindowSpec));
	}
	bool Application::Init() {
		
		if (!mNativeWindow->Init(mConfig)) {
			CORE_LOG_CRITICAL("Window_spec created failed");
			return false;
		}
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
		
}
