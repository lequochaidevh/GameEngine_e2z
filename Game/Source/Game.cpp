#include<VIEngine/Core/Entry.h>
#include<Core/Logger/Logger.h>

class Game : public VIEngine::Application {
public:
	Game(const VIEngine::ApplicationConfiguration& config) : VIEngine::Application(config) {
		std::cout << "Game is config >> Game.cpp\n";
		LOG_INFO("Info works:");
		LOG_TRACE("Trace works");
		LOG_WARN("Warn works");
		LOG_ERROR("Error works");
		LOG_CRITICAL("Critical works");
	}
	virtual bool Init() override {
		std::cout << "Game is init >> Game.cpp\n";
		return true;
	}
	virtual void Shutdown() override {
		std::cout << "Game is shutdown >> Game.cpp\n";
	}

};
VIEngine::Application* VIEngine::CreateApplication() {
	std::cout << "Start CreateApplication >> Game.cpp\n";
	VIEngine::ApplicationConfiguration appConfig;
	appConfig.Width = 800;
	appConfig.Height = 600;
	appConfig.Title = "VIEngine Alpha ver";

	return new Game(appConfig);
}