#include "Window.h"

#include "pch.h"
#include "Core/Logger/Logger.h"
#include "Core/Application.h"
/*6.1.1_Add and define glad and glfw at file.cpp(obligatory)*/
#define GLFW_GL_IMPLEMENTATION
#include <glad/gl.h>
#include<GLFW/glfw3.h>


/*6.2.2_Create GLFWPlatform*/
namespace VIEngine {
	GLFWPlatformWindow::GLFWPlatformWindow() : mWindow(nullptr) , mData() {

	}
	GLFWPlatformWindow::~GLFWPlatformWindow() {
		/*9.1.3.4_Free keyboard and mouse input (mData)*/
		VI_FREE_MEMORY(mData.input.Keyboard);
		VI_FREE_MEMORY(mData.input.Mouse);
	}
	bool GLFWPlatformWindow::Init(const ApplicationConfiguration& config, EventDispatcher* eventDistpatcher) {
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

		/*8.3.7.1_Convert data mEventDispatcher->mData.Dispatcher to refer value into glfwSetWindowSizeCallback(...)*/
		mData.dispatcher = eventDistpatcher;

		/*9.1.2.1_Create Input*/
		mData.input.Keyboard = WindowPlatform::createKeyboard(config.WindowSpec, mWindow);
		mData.input.Mouse = WindowPlatform::createMouse(config.WindowSpec, mWindow);

		glfwSetWindowUserPointer(mWindow, &mData);
		//because the lambda not capture data by reference

		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
			//get data* from EventDispatcher
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->width = width;
			data->height = height;
			WindowResizedEvent eventContext(width, height);
			data->dispatcher->dispatchEventListener<WindowResizedEvent>(eventContext);
			});

		/*9.1.2.2_GLFW Set Callback Mouse and Keyboard*/
		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int keyCode, int scanCode, int action, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			if (action == GLFW_PRESS) {
				data->dispatcher->dispatchEventListener<KeyPressedEvent>({ keyCode });
			}
			else if (action == GLFW_REPEAT) {
				data->dispatcher->dispatchEventListener<KeyHeldEvent>({ keyCode });
			}
			else if (action == GLFW_RELEASE) {
				data->dispatcher->dispatchEventListener<KeyReleasedEvent>({ keyCode });
			}
			});
		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			if (action == GLFW_PRESS) {
				data->dispatcher->dispatchEventListener<MouseButtonPressedEvent>({ button });
			}
			else if (action == GLFW_RELEASE) {
				data->dispatcher->dispatchEventListener<MouseButtonReleasedEvent>({ button });
			}
			});
		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double positionX, double positionY) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			static double lastFrameX = positionX;
			static double lastFrameY = positionY;
			double offsetX = positionX - lastFrameX;
			double offsetY = positionY - lastFrameY;
			data->dispatcher->dispatchEventListener<MouseMovedEvent>({ positionX, positionY, offsetX, offsetY });
			data->input.Mouse->setPosition(positionX, positionY);
			data->input.Mouse->setOffset(offsetX, offsetY);
			lastFrameX = positionX;
			lastFrameY = positionY;
			});
		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double scrollX, double scrollY) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->dispatcher->dispatchEventListener<MouseScrolledEvent>({ scrollX, scrollY });
			data->input.Mouse->setScroll(scrollX, scrollY);
			});

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
	InputState* GLFWPlatformWindow::GetInputState() {
		return &mData.input;
	}
}