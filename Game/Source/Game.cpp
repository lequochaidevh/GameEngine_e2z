#include"VIEngine/Core/Entry.h"
#include<iostream>
//Class inherit
class Game : public VIEngine::Application {
public:
	Game(const VIEngine::ApplicationConfiguration& config) : VIEngine::Application(config) {
		std::cout << "Game is config >> Game.cpp\n";
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