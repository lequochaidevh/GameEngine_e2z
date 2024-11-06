#pragma once
#include "pch.h"
#include "Core/Type/Object.h"
#include "Core/Logger/Logger.h"
#include "Core/Event/EventContext.h"
#include "Core/Memory/MemoryManager.h"
namespace VIEngine {
	template<typename To, typename From>
	VI_FORCE_INLINE To staticCast(From from) { return (To)from; }
	template<typename T>
	T* downCast(Object* obj) {
		if (obj && obj->isDerivedFrom(T::runTimeType)) {
			return (T*)obj;
		}
		return nullptr;
	}
	template<typename T>
	const T* downCast(const Object* obj) {
		if (obj && obj->isDerivedFrom(T::runTimeType)) {
			return (const T*)obj;
		}
		return nullptr;
	}
}