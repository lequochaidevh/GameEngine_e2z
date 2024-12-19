#pragma once

#include "Core/Input/InputState.h"
/*6.2_Config lib-using 	(GLFWPlatform)Library (define override implement function)
						<-Window (enum,class interface NativeWindow [action implement,#(),#~()];(GLFWPlatform:NativeWindow) )
						<-WindowPlatform (NativeWindow* Create()->new GLFWPlatform(),-(),-~())
						<-Application (EWindowSpec(enum),unique_ptr<NativeWindow>)
						<-Client(config)
	by Factory Method Design Pattern */

/*6.2.1_Create Window*/
class GLFWwindow;
namespace VIEngine {
	enum class  EWindowPlatformSpec
	{
		GLFW,
		SDL,
		None
	};


	/*8.3.6_Create EventDispatcher at Window*/
	class EventDispatcher;

	struct ApplicationConfiguration;

	struct WindowData
	{
		int32_t width, height;
		EventDispatcher* dispatcher;

		/*9.1.1.7_Define InputState*/
		InputState input;

	};
	/*8.3.6.1_Add EventDispatcher* at InitWindow */
	class NativeWindow
	{
	public:
		virtual ~NativeWindow() = default;
		virtual bool Init(const ApplicationConfiguration&, EventDispatcher*) = 0;
		virtual void Shutdown() = 0;
		virtual void Swapbuffers() = 0;
		virtual void PollsEvent() = 0;
		virtual bool ShouldClose() = 0;
		/*9.1.2.3_InputState* GetInputState() */
		virtual InputState* GetInputState() = 0;
		
	private:

	protected:
		NativeWindow() = default;
		NativeWindow(NativeWindow&) = default;
	};
	class GLFWPlatformWindow : public NativeWindow
	{
	public:
		GLFWPlatformWindow();
		~GLFWPlatformWindow();
		virtual bool Init(const ApplicationConfiguration&, EventDispatcher*) override;
		virtual void Shutdown() override;
		virtual void Swapbuffers() override;
		virtual void PollsEvent() override;
		virtual bool ShouldClose() override;

		virtual InputState* GetInputState() override;

	private:
		GLFWwindow* mWindow;

		/*8.3.6.2_Add WindowData (-mData) is a member of GLFWPlatformWindow */
		WindowData mData;
	protected:
	};
	
}