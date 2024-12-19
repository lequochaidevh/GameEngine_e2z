#include"spdlog/spdlog.h"
#include"Logger.h"

#include"spdlog/common.h"

namespace VIEngine {
	/*4.1_Give for logger memory by Pointer*/
	Shared<spdlog::logger> Logger::sCoreLogger = nullptr;
	Shared<spdlog::logger> Logger::sClientLogger = nullptr;

	void Logger::Init() {
		/*4.1_Define: Design logger info frame*/ 
		// Example: [22:40:00] [VIEngine::Logger:Init:11] [VIEngine] [Thread:1000] Logger works
		spdlog::set_pattern("%^[%H:%M:%S] [%!:%#] [%n] [Thread:%t] %v%$");

		sCoreLogger = spdlog::stdout_color_mt("VIEngine");
		sCoreLogger->set_level(spdlog::level::trace);

		sClientLogger = spdlog::stdout_color_mt("Client");
		sClientLogger->set_level(spdlog::level::trace);
	}
}