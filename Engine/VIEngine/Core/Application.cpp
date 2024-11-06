#define GLAD_GL_IMPLEMENTATION
#include"Application.h"

#include<GLFW/glfw3.h>
#include "Window/WindowPlatform.h"

/*11.1.10_Define FUNC for iterator -> rend to rbegin at class have vector*/
#define DISPATCH_LAYER_EVENT(eventType, eventContext) for (auto iter = mLayerStack->rbegin(); iter != mLayerStack->rend(); ++iter) {\
	if ((*iter)->on##eventType(eventContext)) {\
		break;\
	}\
}

namespace VIEngine {
	
	Application::Application(const ApplicationConfiguration& config) : mConfig(config), mEventDispatcher(),
		mIsRunning(true), mInputState(nullptr), mTime()
	{
		mNativeWindow.reset(WindowPlatform::Create(config.WindowSpec)); //reset unique_ptr
		/*11.1.7_Add and Allocate Heap mLayerStack*/
		mLayerStack.reset(new LayerStack()); 
	}
	bool Application::Init() {
		
		if (!mNativeWindow->Init(mConfig, &mEventDispatcher)) {
			CORE_LOG_CRITICAL("Window_spec created failed");
			return false;
		}
		/*9.1.3.2_Set value mInputState */
		mInputState = mNativeWindow->getInputState();
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
		/*11.1.9_Browse LayerStack class, this have vector*/

		const float MAX_DELTA_TIME = 0.05f;
		float minDeltaTime = 1.0f / mConfig.MaxFPS;
		while (mIsRunning && !mNativeWindow->ShouldClose()) {
			static float lastFrameTime = 0.0f;

			while (mNativeWindow->getTimeSeconds() - lastFrameTime < minDeltaTime) {} //holding time

			float currentFrameTime = mNativeWindow->getTimeSeconds();
			mTime = currentFrameTime - lastFrameTime;
			lastFrameTime = currentFrameTime;

			mNativeWindow->PollsEvent();

			for (auto layer : *mLayerStack.get()) {
				layer->onRender();
			}

			mNativeWindow->Swapbuffers();
			while (mTime.getDeltaTime() > MAX_DELTA_TIME) {
				for (auto layer : *mLayerStack.get()) { //unique_ptr -> this is address value
					layer->onUpdate(MAX_DELTA_TIME); // operator
				}
				for (auto layer : *mLayerStack.get()) {
					layer->onRender();
				}
				mTime -= MAX_DELTA_TIME;
			}

			for (auto layer : *mLayerStack.get()) { //unique_ptr
				layer->onUpdate(mTime);
			}
			for (auto layer : *mLayerStack.get()) {
				layer->onRender();
			}
		}

		OnShutdownClient();
	}
	void Application::Shutdown() {
		mNativeWindow->Shutdown();
	}

	
	/*9.1.3.3_Define function onEvent*/
	/*11.2.1_Add and Browse rend to rbegin class, this have vector*/
	bool Application::onWindowResizedEvent(const WindowResizedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(WindowResizedEvent, eventContext);
		return false;
	}

	bool Application::onKeyPressedEvent(const KeyPressedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(KeyPressedEvent, eventContext);
		return false;
	}

	bool Application::onKeyHeldEvent(const KeyHeldEvent& eventContext) {
		DISPATCH_LAYER_EVENT(KeyHeldEvent, eventContext);
		return false;
	}

	bool Application::onKeyReleasedEvent(const KeyReleasedEvent& eventContext) {
		if (eventContext.isKey(VIEngine::EKeyCode::ESCAPE)) {
			LOG_TRACE("ESC key is released");
			mIsRunning = false;
		}
		DISPATCH_LAYER_EVENT(KeyReleasedEvent, eventContext);
		return false;
	}

	bool Application::onMouseMovedEvent(const MouseMovedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseMovedEvent, eventContext);
		return false;
	}

	bool Application::onMouseScrolledEvent(const MouseScrolledEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseScrolledEvent, eventContext);
		return false;
	}

	bool Application::onMouseButtonPressedEvent(const MouseButtonPressedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonPressedEvent, eventContext);
		return false;
	}

	bool Application::onMouseButtonHeldEvent(const MouseButtonHeldEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonHeldEvent, eventContext);
		return false;
	}

	bool Application::onMouseButtonReleasedEvent(const MouseButtonReleasedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonReleasedEvent, eventContext);
		return false;
	}
	/*11.2.2_Define func call to func of stackLayer from Application*/
	void Application::pushLayer(Layer* layer) {
		mLayerStack->push(layer);
		layer->onAttach();
	}

	void Application::pushOverlayLayer(Layer* layer) {
		mLayerStack->pushOverlay(layer);
		layer->onAttach();
	}

	void Application::popLayer(Layer* layer) {
		mLayerStack->pop(layer);
		layer->onDetach();
	}

	void Application::popOverlayLayer(Layer* layer) {
		mLayerStack->popOverlay(layer);
		layer->onDetach();
	}
}
