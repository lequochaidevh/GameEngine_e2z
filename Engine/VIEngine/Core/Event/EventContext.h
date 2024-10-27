#pragma once

#include "pch.h"
/*8_Create Event*/

namespace VIEngine {
	/*8.1_Create interface EventContext*/
	class VI_API EventContext {
	public:
		virtual ~EventContext() = default;
	};
	/*8.1.1_Create WindownResizedEvent:EventContext*/
	class VI_API WindowResizedEvent : public EventContext {
	public:
		WindowResizedEvent(int32_t width, int32_t height) : mWidth(width), mHeight(height) {}
		VI_FORCE_INLINE int32_t getWidth() const { return mWidth; }
		VI_FORCE_INLINE int32_t getHeight() const { return mHeight; }
	private:
		int32_t mWidth, mHeight;
	};
}