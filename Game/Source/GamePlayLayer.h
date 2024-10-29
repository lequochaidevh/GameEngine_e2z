#pragma once

/*11.1.5_Add NEW: Layer*/

#include "Core/Layer/LayerStack.h"
#include<Core/Logger/Logger.h>

class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer() {}
	~GameplayLayer() {}
	virtual void onAttach() override {
		LOG_TRACE("GameplayLayer is attached");
	}
	virtual void onDetach() override {
		LOG_TRACE("GameplayLayer is detached");
	}
	virtual bool onKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override {
		LOG_TRACE("Key {0} is pressed", (char)eventContext.getKey());
		return false;
	}
};

class UILayer : public VIEngine::Layer {
public:
	UILayer() {}
	~UILayer() {}
	virtual void onAttach() override {
		LOG_TRACE("UILayer is attached");
	}
	virtual void onDetach() override {
		LOG_TRACE("UILayer is detached");
	}
	virtual bool onKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override {
		LOG_TRACE("Key {0} is pressed on UILayer", (char)eventContext.getKey());
		return true;
	}
	virtual bool onKeyHeldEvent(const VIEngine::KeyHeldEvent& eventContext) override {
		LOG_TRACE("Key {0} is held on UILayer", (char)eventContext.getKey());
		return true;
	}

	virtual bool onKeyReleasedEvent(const VIEngine::KeyReleasedEvent& eventContext) override {
		if (eventContext.isKey(VIEngine::EKeyCode::ESCAPE)) {
			LOG_TRACE("ESC key is released");
		}
		return true;
	}
	virtual bool onMouseButtonPressedEvent(const VIEngine::MouseButtonPressedEvent& eventContext) override {
		if (eventContext.isButton(VIEngine::EMouseButton::BUTTON_LEFT)) {
			LOG_TRACE("Left mouse button is clicked");
		}
		return true;
	}
};