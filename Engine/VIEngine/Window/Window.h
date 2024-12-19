#pragma once

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
	struct WindowData
	{
		int32_t width, height;
		EventDispatcher* dispatcher;
	};
	/*8.3.6.1_Add EventDispatcher* at InitWindow */
	class NativeWindow
	{
	public:
		virtual ~NativeWindow() = default;
		virtual bool Init(const struct ApplicationConfiguration&, EventDispatcher*) = 0;
		virtual void Shutdown() = 0;
		virtual void Swapbuffers() = 0;
		virtual void PollsEvent() = 0;
		virtual bool ShouldClose() = 0;
		
	private:

	protected:
		NativeWindow() = default;
		NativeWindow(NativeWindow&) = default;
	};
	class GLFWPlatformWindow : public NativeWindow
	{
	public:
		virtual bool Init(const struct ApplicationConfiguration&, EventDispatcher*) override;
		virtual void Shutdown() override;
		virtual void Swapbuffers() override;
		virtual void PollsEvent() override;
		virtual bool ShouldClose() override;

		GLFWPlatformWindow();
		~GLFWPlatformWindow();
	private:
		GLFWwindow* mWindow;

		/*8.3.6.2_Add WindowData (-mData) is a member of GLFWPlatformWindow */
		WindowData mData;
	protected:
	};
	
}