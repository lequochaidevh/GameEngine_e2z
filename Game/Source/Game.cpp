#include"VIEngine/Core/Entry.h"
#include"Core/Logger/Logger.h"
#include"VIEngine/Window/Window.h"

#include"GameplayLayer.h"
/*2_Make Client*/
/*2.1_Define Client config*/
/*11.1.6_Config NEW: Layer use func in LayerStack*/
class Game : public VIEngine::Application {
public:
	Game(const VIEngine::ApplicationConfiguration& config) : VIEngine::Application(config) {
		LOG_INFO("Game is config >> Game.cpp:");
	}
	virtual void OnInitClient() override {
		LOG_INFO("Game is init > Game.cpp");

		mLayer = new GameplayLayer();
		mUI = new UILayer();
		pushOverlayLayer(mUI); // >App
		pushLayer(mLayer);
	}
	virtual void OnShutdownClient() override {
		LOG_INFO("Game is shutdown >> Game.cpp ");
		popLayer(mLayer);
		popOverlayLayer(mUI);
	}
private:
	VIEngine::Layer* mLayer, * mUI;
};
VIEngine::Application* VIEngine::CreateApplication() {
	/*2.2_Client init config for Application*/
	VIEngine::ApplicationConfiguration appConfig;
	appConfig.Width = 800;
	appConfig.Height = 600;
	appConfig.Title = "VIEngine Alpha ver";
	appConfig.WindowSpec = VIEngine::EWindowPlatformSpec::GLFW;
	return new Game(appConfig);
}