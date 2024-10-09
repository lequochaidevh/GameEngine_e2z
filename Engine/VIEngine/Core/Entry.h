#include "Application.h"
#include<iostream>
int main() {
	std::cout << "Main Entry.h\n";
	VIEngine::Application* application = VIEngine::CreateApplication();
	std::cout << "After CreateApplication Entry.h\n";
	if (application->Init()) {
		std::cout << "Init Entry.h\n";
		application->Run();
	}

	application->Shutdown();
	delete application;
	return 0;
}