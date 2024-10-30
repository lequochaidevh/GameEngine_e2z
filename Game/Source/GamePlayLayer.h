#pragma once

/*11.1.5_Add NEW: Layer*/

#include "Core/Layer/LayerStack.h"
#include "Core/Logger/Logger.h"

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
	virtual void onUpdate(VIEngine::Time time) {
		LOG_TRACE("{0} Delta Time", time.getDeltaTime());
	}
	
};

