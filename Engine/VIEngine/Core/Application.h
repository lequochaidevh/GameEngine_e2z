#pragma once

#include<glad/gl.h>
#include<iostream>
#include <spdlog/spdlog.h>
#include"Core/Logger/Logger.h"
#include"Window/Window.h"


namespace VIEngine {
	struct VI_API ApplicationConfiguration {
		int Width, Height;
		const char* Title;
		EWindowPlatformSpec WindowSpec;
	};

	class VI_API  Application {
	public:
		virtual ~Application() = default;
		bool Init();
		virtual void OnInitClient() = 0;
		void Run();
		virtual void OnShutdownClient() = 0;
		void Shutdown();
	protected:
		Application() = default;
		Application(const ApplicationConfiguration&);
	private:
		ApplicationConfiguration mConfig;
		Unique<NativeWindow> mNativeWindow;
	};

	extern Application* CreateApplication();
}
