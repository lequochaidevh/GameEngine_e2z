#include"VIEngine/Core/Entry.h"
#include"Core/Logger/Logger.h"
#include"VIEngine/Window/Window.h"

/*2_Make Client*/
/*2.1_Define Client config*/
class Game : public VIEngine::Application {
public:
	Game(const VIEngine::ApplicationConfiguration& config) : VIEngine::Application(config) {
		LOG_INFO("Game is config >> Game.cpp:");
	}
	virtual void OnInitClient() override {
		LOG_INFO("Game is init > Game.cpp");
	}
	virtual void OnShutdownClient() override {
		LOG_INFO("Game is shutdown >> Game.cpp ");
	}

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