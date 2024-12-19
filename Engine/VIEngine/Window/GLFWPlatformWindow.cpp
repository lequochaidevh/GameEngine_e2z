#include "Window.h"

#include "pch.h"
#include "Core/Logger/Logger.h"
#include "Core/Application.h"
#define GLFW_GL_IMPLEMENTATION
#include <glad/gl.h>
#include<GLFW/glfw3.h>

namespace VIEngine {
	GLFWPlatformWindow::GLFWPlatformWindow() : mWindow(nullptr) {

	}
	GLFWPlatformWindow::~GLFWPlatformWindow() {
		
	}
	bool GLFWPlatformWindow::Init(const ApplicationConfiguration& config) {
		if (!glfwInit()) {
			CORE_LOG_CRITICAL("GLFW Init failed");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("GLFW Init success");

		// Setup context for Opengl 4.3 Core
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		mWindow = glfwCreateWindow(config.Width, config.Height, config.Title, nullptr, nullptr);
		if (!mWindow) {
			CORE_LOG_CRITICAL("Window created failed");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("Window created success");
		
		glfwMakeContextCurrent(mWindow);

		//Check to see if window can successfully interact
		if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
			CORE_LOG_CRITICAL("Glad load failed");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("Glad load success");

		return true;
	}
	void GLFWPlatformWindow::Shutdown() {
		glfwTerminate();
	}
	void GLFWPlatformWindow::Swapbuffers() {
		glClearColor(0.3f, 0.3f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mWindow);
	}
	void GLFWPlatformWindow::PollsEvent() {
		glfwPollEvents();
	}
	bool GLFWPlatformWindow::ShouldClose() {
		return glfwWindowShouldClose(mWindow);
	}
}