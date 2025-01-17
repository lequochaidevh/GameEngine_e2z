#pragma once
/*5_Setup Pre-compile header file*/
//Standard Libraty
#include<memory>
#include<stdint.h>
#include<set>
#include<random>
#include<limits>
#include<vector>
#include<string>
#include<bitset>
#include<cassert>
#include<assert.h>
#include<sstream>
#include<istream>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<map>
#include<stack>

template<typename T> using Shared = std::shared_ptr<T>;
template<typename T> using Unique = std::unique_ptr<T>;

//Build .dll

#if ON_VI_ENGINE
#if DYNAMIC_BUILD
#ifdef _MSC_VER
#define VI_API __declspec(dllexport)
#else
#define VI_API __attribute__((visibility("default")))
#endif
#else
#define VI_API
#endif
#else
#if DYNAMIC_IMPORT
#ifdef _MSC_VER
#define VI_API __declspec(dllimport)
#else
#define VI_API
#endif
#else
#define VI_API
#endif
#endif

// Runtime assert
#define VI_ASSERT assert

// Static assert when compile C2607
#if defined(__clang__) || defined(__gcc__)
#define VI_STATIC_ASSERT _Static_assert
#else
#define VI_STATIC_ASSERT static_assert
#endif

// Inline function
#if defined(__clang__) || defined(_gcc__)
#define VI_FORCE_INLINE __attribute__((always_inline)) inline
#define VI_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define VI_FORCE_INLINE __forceinline
#define VI_NOINLINE __declspec(noinline)
#else
#define VI_FORCE_INLINE inline
#define VI_NOINLINE
#endif

// Free memory
#define VI_FREE_MEMORY(memory) if (memory != nullptr) { delete memory; memory = nullptr; }

/*8.3.5.1_Create Lambda: return auto*/
#define BIND_EVENT_FUNCTION(function) [this](auto&... args) -> decltype(auto)\
	{return this->function(std::forward<decltype(args)>(args)...);}

/*10_Setup UUID*/
#define INVALID_ID 0

namespace VIEngine {
	using UUID = size_t;

	UUID VI_API getUUID();

	template<typename T>
	UUID VI_API getTypeUUID() {
		static UUID uuid = getUUID();
		return uuid;
	}
}