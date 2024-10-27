#pragma once

#include<glad/gl.h>
#include<iostream>
#include <spdlog/spdlog.h>
#include"Core/Logger/Logger.h"
#include"Window/Window.h"
#include"Core/Event/EventDispatcher.h"

/*1_Create Application*/
namespace VIEngine {
	/*1.1.3_Config Application*/
	/*6.2.4_Add config choosen*/
	struct VI_API ApplicationConfiguration {
		int Width, Height;
		const char* Title;
		EWindowPlatformSpec WindowSpec; //EWindowPlatformSpec
	};
	/*1.1.1 Application*/
	class VI_API  Application {
	public:
		virtual ~Application() = default;
		/*1.1.1.1_Three basic steps in life of Application. That help me to manage system tightly*/
		virtual void OnInitClient() = 0; //Client
		void Run();//Application
		virtual void OnShutdownClient() = 0;//Client
		
		/*6.1.2_Refactor Application code*/
		bool Init();//Application
		void Shutdown();//Application
		
		
	protected:
		Application() = default; /*1.1.1.2_Singleton design pattern*/
		Application(const ApplicationConfiguration&);
	private:
		/*8.3.4_Create -onWindownResizedEvent(const WindowResizedEvent&) is a func of App Class*/
		bool onWindowResizedEvent(const WindowResizedEvent&);
	private:
		ApplicationConfiguration mConfig;
		Unique<NativeWindow> mNativeWindow; //unique_ptr<NativeWindow>
		/*8.3.3_Create mEventDispatcher is a member of Application*/
		EventDispatcher mEventDispatcher;
	};
	/*1.1.2_Application will be managed by Engine*/
	extern Application* CreateApplication(); /*using extern key because function will defined in other project*/
}
