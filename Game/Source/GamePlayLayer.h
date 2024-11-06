#pragma once

#include "Core/Layer/Layer.h"

class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer();
	~GameplayLayer();

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(VIEngine::Time time);
	virtual bool onKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext);
};