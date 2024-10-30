#pragma once
#include"pch.h"

/*12.1.1_Create Time */
namespace VIEngine {
	class VI_API Time {
	public:
		Time() = default;
		Time(float deltaTime) : mDeltaTime(deltaTime), mTimeScale(1.0f) {
		}
		~Time() = default;
		VI_FORCE_INLINE float getDeltaTime() const { return mDeltaTime; }
		VI_FORCE_INLINE void setDeltaTime(float value) { mDeltaTime = value; }
		VI_FORCE_INLINE float getTimeScale() const { return mTimeScale; }
		VI_FORCE_INLINE void setTimeScale(float value) { mTimeScale = value; }

		VI_FORCE_INLINE friend Time& operator+=(Time& t1, const Time& t2) { t1.mDeltaTime += t2.getDeltaTime(); return t1; }

		VI_FORCE_INLINE friend bool operator>=(const Time& t1, const Time& t2) { return t1.mDeltaTime >= t2.getDeltaTime(); }
		VI_FORCE_INLINE friend bool operator>(const Time& t1, const Time& t2) { return t1.mDeltaTime > t2.getDeltaTime(); }

		VI_FORCE_INLINE friend bool operator<=(const Time& t1, const Time& t2) { return t1.mDeltaTime <= t2.getDeltaTime(); }
		VI_FORCE_INLINE friend bool operator<(const Time& t1, const Time& t2) { return t1.mDeltaTime < t2.getDeltaTime(); }

		VI_FORCE_INLINE friend Time& operator-=(Time& t1, const Time& t2) { t1.mDeltaTime -= t2.getDeltaTime(); return t1; }
	private:
		float mDeltaTime, mTimeScale;
	};
}
