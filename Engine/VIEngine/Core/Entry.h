#pragma once
/*3_Conect point between APPLICATION and CLIENT*/
#include"Application.h"


int main() {
	VIEngine::Logger::Init();
	CORE_LOG_INFO("Main >> Entry.h");
	/*3.1_Start Client: Game*/
	VIEngine::Application* application = VIEngine::CreateApplication(); // Application->Client: Game with config
	CORE_LOG_INFO("After CreateApplication >> Entry.h");
	if (application->Init())
	{
		CORE_LOG_INFO("Init VIEngine::Application >> Entry.h");
		application->Run();
	}

	application->Shutdown();
	VI_FREE_MEMORY(application);

	std::cin.get();

	return 0;
}