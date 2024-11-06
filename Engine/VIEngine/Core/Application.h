#pragma once

#include <glad/gl.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include "Core/Logger/Logger.h"
#include "Window/Window.h"
#include "Window/WindowPlatform.h"
#include "Core/Event/EventDispatcher.h"
#include "Core/Layer/LayerStack.h"
#include "Core/Time/Time.h"
/*1_Create Application*/
namespace VIEngine {
	/*1.1.3_Config Application*/
	/*6.2.4_Add config choosen*/
	struct VI_API ApplicationConfiguration {
		int Width, Height;
		const char* Title;
		EWindowPlatformSpec WindowSpec; //EWindowPlatformSpec
		uint16_t MaxFPS;
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
		
		void pushLayer(Layer*);
		void pushOverlayLayer(Layer*);
		void popLayer(Layer*);
		void popOverlayLayer(Layer*);
	protected:
		Application() = default; /*1.1.1.2_Singleton design pattern*/
		Application(const ApplicationConfiguration&);
	private:
		/*8.3.4_Create -onWindownResizedEvent(const WindowResizedEvent&) is a func of App Class*/
		bool onWindowResizedEvent(const WindowResizedEvent&);


		bool onKeyPressedEvent(const KeyPressedEvent&);
		bool onKeyHeldEvent(const KeyHeldEvent&);
		bool onKeyReleasedEvent(const KeyReleasedEvent&);
		bool onMouseMovedEvent(const MouseMovedEvent&);
		bool onMouseScrolledEvent(const MouseScrolledEvent&);
		bool onMouseButtonPressedEvent(const MouseButtonPressedEvent&);
		bool onMouseButtonHeldEvent(const MouseButtonHeldEvent&);
		bool onMouseButtonReleasedEvent(const MouseButtonReleasedEvent&);
	private:
		ApplicationConfiguration mConfig;
		Unique<NativeWindow> mNativeWindow; //unique_ptr<NativeWindow>
		Unique<LayerStack> mLayerStack;

		/*8.3.3_Create mEventDispatcher is a member of Application*/
		EventDispatcher mEventDispatcher;

		class InputState* mInputState;

		Time mTime;
		bool mIsRunning;
	};
	/*1.1.2_Application will be managed by Engine*/
	extern Application* CreateApplication(); /*using extern key because function will defined in other project*/
}
