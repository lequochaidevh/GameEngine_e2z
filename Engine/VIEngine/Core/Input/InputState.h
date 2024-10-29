#pragma once
#include"pch.h"
#include"KeyCode.h"

class GLFWwindow;

namespace VIEngine {
	/*9.1.1.1_Interface KeyboardInput*/
	class VI_API KeyboardInput {
	public:
		virtual ~KeyboardInput() = default;
		//getValue-> replace func isHeld not use at glfw
		VI_FORCE_INLINE int8_t getValue(EKeyCode keyCode) const { return (isPressed(keyCode) || isHeld(keyCode)) ? 1 : 0; }

		VI_FORCE_INLINE EKeyState getState(EKeyCode keyCode) { return getState((int32_t)keyCode); }
		VI_FORCE_INLINE bool isPressed(EKeyCode keyCode) const { return isPressed((int32_t)keyCode); }
		VI_FORCE_INLINE bool isHeld(EKeyCode keyCode) const { return isHeld((int32_t)keyCode); } //Can not use by glfw
		VI_FORCE_INLINE bool isReleased(EKeyCode keyCode) const { return isReleased((int32_t)keyCode); }

		virtual EKeyState getState(int32_t keyCode) const = 0;
		virtual bool isPressed(int32_t keyCode) const = 0;
		virtual bool isHeld(int32_t keyCode) const = 0;
		virtual bool isReleased(int32_t keyCode) const = 0;
	protected:
		KeyboardInput() = default;
	};
	/*9.1.1.2_Create GLFWKeyboard: KeyboardInput*/
	class VI_API GLFWKeyboardInput : public KeyboardInput {
	public:
		GLFWKeyboardInput(void* window);
		virtual EKeyState getState(int32_t keyCode) const override;
		virtual bool isPressed(int32_t keyCode) const override;
		virtual bool isHeld(int32_t keyCode) const override;
		virtual bool isReleased(int32_t keyCode) const override;
	private:
		GLFWwindow* mWindow;
	};
	/*9.1.1.5_Interface MouseInput & GLFWMouseInput:*/
	class VI_API MouseInput {
	public:
		virtual ~MouseInput() = default;
		VI_FORCE_INLINE int8_t getValue(EMouseButton button) const { return (isPressed(button) || isHeld(button)) ? 1 : 0; }

		VI_FORCE_INLINE EKeyState  getState(EKeyState  button) { return getState((int32_t)button); }
		VI_FORCE_INLINE bool isPressed(EMouseButton button) const { return isPressed((int32_t)button); }
		VI_FORCE_INLINE bool isHeld(EMouseButton button) const { return isHeld((int32_t)button); } //Can not use by glfw
		VI_FORCE_INLINE bool isReleased(EMouseButton button) const { return isReleased((int32_t)button); }
		virtual EKeyState  getState(int32_t button) const = 0;
		virtual bool isPressed(int32_t button) const = 0;
		virtual bool isHeld(int32_t button) const = 0;
		virtual bool isReleased(int32_t button) const = 0;

		VI_FORCE_INLINE float getPositionX() const { return mX; }
		VI_FORCE_INLINE float getPositionY() const { return mY; }
		VI_FORCE_INLINE float getOffsetX() const { return mOffsetX; }
		VI_FORCE_INLINE float getOffsetY() const { return mOffsetY; }
		VI_FORCE_INLINE float getSrollX() const { return mScrollX; }
		VI_FORCE_INLINE float getSrollY() const { return mScrollY; }

		VI_FORCE_INLINE void setPosition(float x, float y) { mX = x; mY = y; }
		VI_FORCE_INLINE void setPositionX(float x) { mX = x; }
		VI_FORCE_INLINE void setPositionY(float y) { mY = y; }

		VI_FORCE_INLINE void setOffset(float offsetX, float offsetY) { mOffsetX = offsetX; mOffsetY = offsetY; }
		VI_FORCE_INLINE void setOffsetX(float offsetX) { mOffsetX = offsetX; }
		VI_FORCE_INLINE void setOffsetY(float offsetY) { mOffsetY = offsetY; }

		VI_FORCE_INLINE void setScroll(float scrollX, float scrollY) { mScrollX = scrollX; mScrollY = scrollY; }
		VI_FORCE_INLINE void setSrollX(float scrollX) { mScrollX = scrollX; }
		VI_FORCE_INLINE void setSrollY(float scrollY) { mScrollY = scrollY; }


	protected:
		MouseInput() = default;
	protected:
		float mX, mY;
		float mOffsetX, mOffsetY;
		float mScrollX, mScrollY;
	};

	class VI_API GLFWMouseInput : public MouseInput {
	public:
		GLFWMouseInput(void* window);
		virtual EKeyState getState(int32_t button) const override;
		virtual bool isPressed(int32_t button) const override;
		virtual bool isHeld(int32_t button) const override;
		virtual bool isReleased(int32_t button) const override;
	private:
		GLFWwindow* mWindow;
	};
	struct VI_API InputState {
		KeyboardInput* Keyboard;
		MouseInput* Mouse;
	};

}