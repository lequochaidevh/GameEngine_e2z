#include<VIEngine/Core/Entry.h>
#include<Core/Logger/Logger.h>

class Game : public VIEngine::Application {
public:
	Game(const VIEngine::ApplicationConfiguration& config) : VIEngine::Application(config) {
		LOG_INFO("Game is config >> Game.cpp:");
		
	}
	virtual bool Init() override {
		LOG_INFO("Game is init > Game.cpp");
		return true;
	}
	virtual void Shutdown() override {
		LOG_INFO("Game is shutdown >> Game.cpp ");
	}

};
VIEngine::Application* VIEngine::CreateApplication() {
	//
	VIEngine::ApplicationConfiguration appConfig;
	//LOG_INFO("Start CreateApplication >> Game.cpp");
	appConfig.Width = 800;
	appConfig.Height = 600;
	appConfig.Title = "VIEngine Alpha ver";

	return new Game(appConfig);
}