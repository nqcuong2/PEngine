#pragma once

#ifdef PENGINE_PLATFORM_WINDOWS
	#ifdef PENGINE_BUILD_DLL
		#define PENGINE_API __declspec(dllexport)
	#else
		#define PENGINE_API __declspec(dllimport)
	#endif
#else
	#error Hazel only supports Windows!
#endif // PENGINE_PLATFORM_WINDOWS

#ifdef PENGINE_DEBUG
	#define PENGINE_ENABLE_ASSERTS
#endif

#ifdef PENGINE_ENABLE_ASSERTS
	#define PE_ASSERT(x, ...) { if (!(x)) { PE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PE_CORE_ASSERT(x, ...) { if (!(x)) { PE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PE_ASSERT(x, ...)
	#define PE_CORE_ASSERT(x, ...)
#endif // PENGINE_ENABLED_ASSERTS


#define BIT(x) (1 << x)

#define PE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)