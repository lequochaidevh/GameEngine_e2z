#pragma once
#include"pch.h"
#include"Core/Event/EventContext.h"

/*11.1.1_Create LayerClass*/
namespace VIEngine {
	class VI_API Layer {
	public:
		Layer() {
			mID = getUUID();
		}
		virtual ~Layer() = default;
		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onProcessInput(const struct InputState&) {}
		virtual void onUpdate(float deltaTime) {}
		virtual void onRender() {}

		/*11.1.2_Reference Application ;Action: Event > Application > Layer*/
		virtual bool onWindowResizedEvent(const WindowResizedEvent&) { return false; }
		virtual bool onKeyPressedEvent(const KeyPressedEvent&) { return false; }
		virtual bool onKeyHeldEvent(const KeyHeldEvent&) { return false; }
		virtual bool onKeyReleasedEvent(const KeyReleasedEvent&) { return false; }
		virtual bool onMouseMovedEvent(const MouseMovedEvent&) { return false; }
		virtual bool onMouseScrolledEvent(const MouseScrolledEvent&) { return false; }
		virtual bool onMouseButtonPressedEvent(const MouseButtonPressedEvent&) { return false; }
		virtual bool onMouseButtonHeldEvent(const MouseButtonHeldEvent&) { return false; }
		virtual bool onMouseButtonReleasedEvent(const MouseButtonReleasedEvent&) { return false; }
	private:
		UUID mID;
	};
}