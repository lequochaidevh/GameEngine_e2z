
#include"Application.h"

namespace VIEngine {
    Application::Application(const ApplicationConfiguration& config) : mConfig(config) {
        Logger::Init();
		CORE_LOG_INFO("Info works:");
		CORE_LOG_TRACE("Trace works");
		CORE_LOG_WARN("Warn works");
		CORE_LOG_ERROR("Error works");
        CORE_LOG_CRITICAL("Critical works");
        
	}

	void Application::Run() {
		std::cout << "App is running: " << mConfig.Width << ", " << mConfig.Height << ", " << mConfig.Title << std::endl;
	}
		
}
